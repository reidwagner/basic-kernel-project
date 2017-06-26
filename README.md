# BKP

This kernel has been put together for learning purposes.

Sources:
* https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf (most boot code)
* http://wiki.osdev.org/
* http://www.brokenthorn.com/Resources/OSDevIndex.html
* http://arjunsreedharan.org/

Running:

* Qemu:
```make qemu```

* Qemu in terminal:
```make curses```

* Bochs:
```make bochs```

To create an iso:
```mkisofs -o bkp.iso -V BKP -b bkp.img <directory with only bkp.img>```
