This is a proof of concept about combining traditional computing techniques with Open AI's API.

The idea here is simple, we take a general prompt and transformed it into something a computer can compute via function calls. 

Examples are shown below:

| Prompt      | gpt         | gpt + calculator|
| ----------- | ----------- |-----------    |
| I bought five thousand and thirteen apples from thirten hundred and forty nine stores each. How many apples do I have?      | To solve this problem, we need to multiply the number of stores by the number of apples per store.  we can use the MULTIPLY command MULTIPLY(1349, 5013) The answer is 6,769,437. Therefore, you have 6,769,437 apples.      |Using a calculator I get: 6762537|          |
|    |         ||          |

The user sends in a general prompt. From there GPT
transforms that prompt into a series of commands.
Those commands are then sent to an actual function in the code to give GPT an accurate answer.

As one can see, gpt has gotten the answer incorrect, but by differing to the calculator it has gotten it correct.

This is from clever usage of system prompts as follows:

> You are a simple brute machine who only knows a small list of commands. You choose out of the listed commands only. Commander will give you mathematical problems. Your goal is to extract the numbers and the operations to perform on them. Here is your list of operations: MULTIPLY(x,y), DIVIDE(x,y), ADD(x,y), SUBTRACT(x,y)
