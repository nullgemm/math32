# Math32
Math32 is a patchwork integer math library. Most of the routines come
from Hacker's Delight and some others were gathered from the internet.

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
