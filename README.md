# Abdul Raheem (ar1712) and Siddharth Sircar (ss3777)

This project provides an enhanced version of malloc and free from the stdlib library of C. Before allocating or freeing memory, the program first checks for erros and reports them to the console.

The c program memgrind tests it using 5 main tests:

* First, it attempts to allocate more memory than is available. This test took around .00009 seconds.

* Second, it allocates 120 bytes of memory and immediately frees it. This test took around .000006 seconds.

* Third, it allocates 120 byte of memory, but tries to free it twice. This test took around .000005 seconds.

* Fourth, it allocates 120 bytes of memory three times, frees one, and then tries to allocate another. This test took around .000003 seconds.

* Fifth, it allocates three chunks of memory, one containing 120 bytes, one 60 bytes, and one 20 bytes. This test took .000004 seconds.
