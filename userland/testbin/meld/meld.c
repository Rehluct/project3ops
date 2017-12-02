
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

int
main(int argc, char *argv[])
{
	static char writebuf1[16] = "AAAABBBBCCCCDDDD";
	static char writebuf2[16] = "eeeeffffgggghhhh";
  static char readbuf[17];

	const char *file1, *file2, *mergefile;
	int fd, rv;

	if (argc == 2) {
          file1 = argv[1];
     }
    else if(argc > 2){
		errx(1, "Usage: meld");
	}

     file1 = "test1";
     file2 = "test2";
     mergefile= "merged";


	fd = open(file1, O_WRONLY|O_CREAT|O_TRUNC, 0664);
	if (fd<0) {
		err(1, "%s: open for write", file1);
	}

	rv = write(fd, writebuf1, 8);
	if (rv<0) {
		err(1, "%s: write", file1);
	}

	rv = close(fd);
	if (rv<0) {
		err(1, "%s: close", file1);
	}

     fd = open(file2, O_WRONLY|O_CREAT|O_TRUNC, 0664);
     if (fd<0) {
          err(1, "%s: open for write", file2);
     }

     rv = write(fd, writebuf2, 8);
     if (rv<0) {
          err(1, "%s: write", file2);
     }

     rv = close(fd);
     if (rv<0) {
          err(1, "%s: close (1st time)", file2);
     }

     printf("Melding...\n");
     int bytes = meld(file1, file2, mergefile);

     if (bytes<0) {
          err(1, "%s: merging", mergefile);
     }

     printf("Reading merged file...\n");
	fd = open(mergefile, O_RDONLY);
	if (fd<0) {
		err(1, "%s: open for read", mergefile);
	}

	rv = read(fd, readbuf, 16);
	if (rv<0) {
		err(1, "%s: read", mergefile);
	}

	rv = close(fd);

	if (rv<0) {
		err(1, "%s: close (merge)", mergefile);
	}
	/* ensure null termination */
	readbuf[16] = 0;

}
