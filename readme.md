# Math32
Math32 is a patchwork integer math library gathering the best routines
I was able to find in papers, in litterature and on the vast internet.

# Boring legal stuff you're actually going to love
All the code in this repo can be safely licensed under WTFPL because all
the routines were re-written from scratch using the original concepts.

In theory the original author of one of these algorithms can register
a patent on its integration in a system that performs a specific task.

He wouldn't be able to register a patent for the algorithm only though,
as they are considered abstract ideas, which you simply can't patent.

```
For example, RSA cryptography is not and can't be patented.
The use of RSA to secure communications on a computer system is.
```

This means the algorithms in this repo will be safe forever.
Your use of these algorithms could be attacked, though.
But that would be patent trolling. Duh.

## Accuracy
Math32 does not make any approximation. All the functions return the
integer part of the real result and were successfully brute-tested
with every valid 32-bit integer possible.

You can brute-test them yourself with the following command
(it only takes a few minutes on my computer)
```
make github # or 'make gitea' if you cloned this from git.cylgom.net
make
make run
```

## Greetings
Everyone hacking in their batcave.
