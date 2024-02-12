# Minitalk :phone:

## :teacher: Theory

* [Data types](#char--int-a-world-of-formatted-0s-and-1s)
* [Bitwise Operatrions](#bitwise-operations)
* [Signals and sigaction](#structure-of-sigaction)

## :computer: Code

## Char & Int: A world of formatted 0s and 1s

So far, we mostly handled type defined char / int type variable, which are an easy way to deal with stored variables for new users. In background, type declaration is a way to tell the compiler how many bits compose the information we stored. Whenever we do pointer operations such as `pointer + 1`, this tells the compiler to increase the pointer value of `sizeof(type)`. In case of a `void pointer` the compiler would not be able to understand the instruction `pointer + 1`. 🤔 It does not understand what that means, because the void type does not have that information!<br>
Therefore, it is fundamental to understand the behind the scene of these types and what cool things can be done with them.

## Type storage

Fundamental knowledge: `8 bit = 1 Byte` <br>
Possible combinations x Byte: `2^(8 * #Bytes)`

> Check Born2Beroot for more about the GiB vs GB differences

Any built-in data types are a way to say to the computer how many sets of 8 bit or bytes he needs to read in order to properly evaluate the stored value for the specific variable.

| type | Byte size | Range | Notes |
|------:|:-------:|:---------:|:--|
| char | 1 Byte | -128:127 | 1st bit is set either to 1 (negative) or 0 (positive) |
| unsigned char | 1 Byte | 0:255 | Only represents positive values |
| int | 4 Bytes | -2^31-1:2^31 | 1st bit is set for the sign (see char)
| unsigned int | 4 Bytes | 0 : 2^32 | Only represents positive values
| long int | 8 Bytes | -2^63 -1:2^63 | Stores the variable value in a 8 Byte

Whenever we pass information to functions like `printf` or `var_arg` (see [`ft_printf`](https://github.com/pineppa/42_1_FT_Printf)), we are explaining to the compiler the datatype of the variables we passed in so that it can correctly read the stored information and properly handle memory pointers. This is way the compiler is confused when we attempt to sum 1 to a void pointer...

## Bitwise operations

Bitwise operations refers to binary mathematics applied directly to the bits representation of a char or of an int. More than normal sums or differences, bitwise operations apply more often to logic operations (AND, OR, XOR, NOT) and combination of them.

### Sums and differences

Like normal mathematical operations, sum of two numbers happens in a binary representation instead of a decimal one. The same can be used for char in the ASCII table. An interesting example is to capitalize a letter, since letters are always 32 position aparts, or `00100000` in bit representation. So:
Operation | Transformation (Letters) | Transformation (Base 10) | Transformation (Base 2) |
|:-:|:------:|:------:|:---|
| + | A -> a | 65 -> 97 | 01000001 +<br>00100000 =<br>-------------<br>01100001 |
| - | a -> A | 97 -> 65 | 01100001 -<br>00100000 =<br>-------------<br>01000001 |

What happens when logic operators are used? Chaos... or cryptography!

To apply bitwise logical operations we need to use a single `|` for OR or `$` for AND. For simplicity, we will consider an "unsigned char"

Operation | Operation Usage | Output | Transformation (Base 2) | Notes
|:-:|:------:|:------:|:---|:---|
| \| | `c` \| `)` | `k` | 01100011 OR<br>00101001 =<br>-------------<br>01101011 | Since the 2^5 bit and the 2^0 is 1 for both, 32 and 1 do not get added.<br>So `99 \| 41 = 107` which is the letter `k` |
| \& | `c` & `)` | `!` | 01100011 AND<br>00101001 =<br>-------------<br>00100001 | Since the 2^6 and 2^3 bits are different they are not considered.<br>So `99 & 41 = 33` which is the esclamation point `!` |
| \^ | `c` \^ `)` | `` | 01100011 XOR<br>00101001 =<br>-------------<br>01001010 | Since the 2^5 bit and the 2^0 is 1 for both, 32 and 1 do not get added.<br>So `99 ^ 41 = 74` which is the letter `J` |
| tilde | tilde `c` | Extended ASCII | bitwise NOT<br>01100011 -> 10011100 | This moves the value from 99 to `256 - 99 = 157` which is part of the extended ASCII. |
| >> | >>`c` | Extended ASCII | Move right<br>01100011 -> 00110001 | This moves the bits position right and adds a 0 at the start.
| << | <<`c` | Extended ASCII | bitwise NOT<br>01100011 -> 10011100 | This moves the bits position left and adds a 0 at the end.

A few interesting things:

* XOR logic can be used to switch from *Upper* to *Lower* case and viceversa, since this will always switch the value of the 2^5 bit;
* A bitwise NOT is like a XOR between 11111111 and the 8 bits value;
* `>>` and `<<` are equivalent to a division by 2 and a multiplication by 2;

## Processes and PID
This topic will be discussed way more in depth in the next projects (Philosophers), therefore let's limit ourselves to the basics.

PID is the Process IDentification number of any process running on the computer. Very low numbers are usually associated to kernel processes and is best not to touch them. In general, as a rule of thumbs, these are defined for values lower than 300.
Moreover, an architecture with 32-bit can store up to 2^15 process, while a 64-bit can reach 2^22 processes. However, it is a good practice to limit and use processes of the 32-bit. Since the maximum value achievable is lower than INT_MAX, we limit the user possibility to 2^22.

## UNICODE and UTF-8

The Unicode Standard, is a text encoding standard designed to support more than 256 characters as defined per the ASCII tables (expanded version included). Thanks to the UNICODE standard, it is possible to write in all the different languages of the world, add emojis to the text and include mathematical operators or other symbols.

The most commonly used standard is the UTF-8. It is composed of 1 to 4 bytes, which can be visualised as a combination of 1 to 4 char. Other standards like UTF-16 or UTF-32 are also composed of a maximum of 4 bytes, similarly to UTF-8, but each combination works with a fixed size of memory. This is 2 times 2 bytes (16bits) for UTF-16 and a fixed size of 4 bytes for UTF-32.

Unicode characters reference in HTML code uses the format `&#nnnn` or `&#xhhhh`;<br>
Some example:

| Unicode | Character | ASCII Value | Octal Value |
| :-: | :-: | :-: | :-: |
| U+0064 | d | 100 | 144 |
| U+0021 | ! | 33 | 41 |
| U+1F60E | 😎 | / | / |

For this project, handling of Unicode characters is directly taken care from the terminal in which we are running our program, therefore the mandatory part takes care of the bonus part as well.

## Code explaination

This project requires the creation of 2 programs, a client and a server, which needs to be able to communicate with each others via the usage of signals. To accomplish this, the client will deconstruct the message bit by bit and the server will be able to reconstruct it.

## Structure of sigaction

```
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, ucontext_t *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};
```

* `sa_handler`: Basic function used to handle signals;
* `sa_sigaction`: More structured function to handle a signals, with additional signal and context information;
> NOTE: On some architectures a union is involved. So, do not assign a funciton to both `sa_handler` and `sa_sigaction`;
* `sa_mask`: Governs the set of signals that are allowed to be triggered and used;
* `sa_flags`: Are used to specify specific behaviors when the handler is called;

* `sigaction(int SIG, struct sigaction sa, void* oaction)`: Whenever a SIG is received, the signal is handled by the second parameter. It can point to a SIG_IGN value, that ignores the signal, .. or it can point to a sigaction structure that describes the action to be taken upon receipt of the signal parameter SIG. The third parameter is often set to a NULL pointer and it points to a sigaction structure in which the signal action data in effect at the time of the sigaction subroutine is returned.

More information can be read in the `man sigcaction` or at [IBM's documentation](https://www.ibm.com/docs/en/aix/7.3?topic=s-sigaction-sigvec-signal-subroutine)

## 🤬 Handling the passage of information

Communications via machines or internal processes is usually done as a serie of `0`s & `1`s. Among the signals defined, the user is allowed to assign an arbitrary meaning to `SIGUSR1` & `SIGUSR2`. We will use `SIGUSR1` as a value of `0` and `SIGUSR2` as a value of `1`. In order to send complex information such as characters or a text, we need to deconstruct the values in the bits it is composed of and transfer them one by one.

Building on **[bitwise arithmetics](#bitwise-operations)**, we can read the set of bits of a character and send the proper signal. For example, given the letter `d`:

| Char | bit representation | bitwise operation |
|:-:|:-:|:-:|
| `d` | 01100100 | `d>>7 == 00000000`<br>`d>>6 == 00000001`<br>`d>>5 == 00000011`<br>`d>>4 == 00000110`<br>`d>>3 == 00001100`<br>`d>>2 == 00011001`<br>`d>>1 == 00110010`

The last digit of each number, represents a the bit value for the character we are trying to send. Therefore, checking the char `mod 2` will return `0` in case the last bit is `0` otherwise `1` in case the last bit is `1`.

Similarly to reconstruct the code, we will receive the message bit by bit. Once we received a bit, we can use the operator `<<` to move left the last received bit information and get ready to receive a new one. Once every 8 bits received, we will have properly reconstructed a character that can be printed on screen.
