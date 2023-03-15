#include <stdio.h>
#include <iostream>
#include "../include/openai/openai.hpp"
#include "../include/openai/json.hpp"
#include <string>

using namespace std;
using namespace nlohmann::json_abi_v3_11_2;

int MULTIPLY(int x, int y);
float DIVIDE(float x, float y);
int ADD(int x, int y);
int SUBTRACT(int x, int y);
int PerformCalculation(string content);
int GetResult(int option, string content, int index);

int main()
{ 
    // Send a prompt to OpenAI chat.
    openai::start();

    cout << "Type in a question to ask OpenAI: " << '\n';
    string prompt;
    getline(cin, prompt);

    string system = "You are a simple brute machine who only knows a small list of commands. You choose out of the listed commands only. Commander will give you mathematical problems. Your goal is to extract the numbers and the operations to perform on them. Here is your list of operations: MULTIPLY(x,y), DIVIDE(x,y), ADD(x,y), SUBTRACT(x,y)";
    
    json request = R"(
    {
        "model": "gpt-3.5-turbo",
        "messages":[{"role":"system", "content":"system"}, {"role":"user", "content":"prompt"}],
        "max_tokens": 200,
        "temperature": 0
    }
    )"_json;

    request["messages"][0]["content"] = system;
    request["messages"][1]["content"] = prompt;



    auto chat = openai::chat().create(request);

    cout << chat["choices"][0]["message"]["content"] << '\n' << "Using a calculator I get: "  << PerformCalculation(chat["choices"][0]["message"]["content"]) << '\n';
}

int PerformCalculation(string content)
{
    int option = 0;
    int result = 0;
    //walk through string.
    string currentString = "";
    for(int i = 0; i < content.length(); i++)
    {
        
        if(currentString == "MULTIPLY(")
        {
            option = 1;
            result = GetResult(option, content, i);
            return result;
        }
        else if(currentString == "DIVIDE(")
        {
            option = 2;
            result = GetResult(option, content, i);
            return result;
        }
        else if(currentString == "ADD(")
        {
            option = 3;
            result = GetResult(option, content, i);
            return result;
        }
        else if(currentString == "SUBTRACT(")
        {
            option = 4;
            result = GetResult(option, content, i);
            return result;
        }
        else if(content[i] == ' ')
        {
            currentString = "";
            continue;
        }
        else if (content[i] == '\n')
        {
            currentString = "";
            continue;
        }
        currentString += content[i];
    }
    return result;
}

int GetResult(int option, string content, int index)
{
    int result = 0;
    string x = "";
    string y = "";

    bool create_x = true;
    for(int i = index; i < content.length(); i++)
    {

        if(content[i] == ',')
        {
            create_x = false;
            continue;
        }
        else if(content[i] == ')')
        {
            break;
        }

        if(content[i] == ' ')
        {
            continue;
        }

        if(create_x)
        {
            x += content[i];  
        }
        else
        {
            y += content[i];
        }
    }

    int xInt = stoi(x);
    int yInt = stoi(y);
    
    switch(option)
    {
        case 1:
            result = MULTIPLY(xInt, yInt);
            break;
        case 2:
            result = DIVIDE(xInt, yInt);
            break;
        case 3:
            result = ADD(xInt, yInt);
            break;
        case 4:
            result = SUBTRACT(xInt, yInt);
            break;
    }
    return result;
}

int MULTIPLY(int x, int y)
{
    return x * y;
}

float DIVIDE(float x, float y)
{
    return x / y;
}

int ADD(int x, int y)
{
    return x + y;
}

int SUBTRACT(int x, int y)
{
    return x - y;
}
