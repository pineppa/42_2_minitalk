# Minitalk :phone:

## :teacher: Theory

* [Data types](#char--int-a-world-of-formatted-0s-and-1s)
* [Bitwise Operatrions](#bitwise-operations)
* [Signals and sigaction](#structure-of-sigaction)

## :computer: Code

## Char & Int: A world of formatted 0s and 1s

So far, we mostly handled type defined char / int which are easy to visualise for new user. However, it is fundamental to understand the behind the scene of these types and what cool things can be done with them.

## Type storage

Fundamental knowledge: `8 bit = 1 Byte` <br>
Combinations x Byte: `2^(8*#Bytes)`

> Check Born2Beroot for more about the GiB vs GB differences

Any built-in data types are a way to say to the computer how many sets of 8 bit or bytes he needs to read in order to properly evaluate the stored value for the specific variable.

| type | Byte size | Range | Notes |
|------:|:-------:|:---------:|:--|
| char | 1 Byte | -128:127 | 1st bit is set either to 1 (negative) or 0 (positive) |
| unsigned char | 1 Byte | 0:255 | Only represents positive values |
| int | 4 Bytes | -2^31-1:2^31 | 1st bit is set for the sign (see char)
| unsigned int | 4 Bytes | 0 : 2^32 | Only represents positive values
| long int | 8 Bytes | -2^63 -1:2^63 | Stores the variable value in a 8 Byte

Whenever we pass information to functions like printf or var_arg (see ft_printf), we are explaining to the compiler how to read the memory and how to properly move pointers. This is way the compiler is confused when we attempt to sum 1 to a void pointer... It does not understand what that means, because the void type does not have that information!

## Bitwise operations

Bitwise operations refers to binary mathematics applied directly to the bits representation of a char or of an int. More than normal sums or differences, bitwise operations apply more often to logic operations (AND, OR, XOR, NOT) and combination of them.

### Sums and differences

Like normal mathematical operations, sum of two numbers happens in a binary representation instead of a decimal one. The same can be used for char in the ASCII table. An interesting example is to capitalize a letter, since letters are always 32 position aparts, or `00100000` in bit representation. So:
Operation | Transformation (Letters) | Transformation (Base 10) | Transformation (Base 2) |
|:-:|:------:|:------:|:---|
| + | A -> a | 65 -> 97 | 01000001 +<br>00100000 =<br>-------------<br>01100001 |
| - | a -> A | 97 -> 65 | 01100001 -<br>00100000 =<br>-------------<br>01000001 |

What happens when logic operators are used? Chaos... or cryptography
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

## Code explaination

This project requires the creation of 2 programs, a client and a server, which needs to be able to communicate with each others via the usage of signals. To accomplish this, the client will deconstruct the message bit by bit and the server will be able to reconstruct it.

## Structure of sigaction

```
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};
```

* `sa_handler`: Function that is activated in order to handle a specific signal;
* `sigaction(SIG, struct sigaction sa, Previous signal?)` binds sa to the signal raised by SIG;
> NOTE: On some architectures a union is involved: do not assign to both `sa_handler` and `sa_sigaction`;
* `sa_mask`: Governs the set of signals that are allowed to be triggered and used;
* `sa_flags`: Are used to specify specific behaviors when the handler is called;

## Questions

* ASCII is cool, but what about UTF-8?
    * Suspect: UTF-8 or Unicode with 8 bits, should work as a series of characters to represent as many values as stored in a int;
