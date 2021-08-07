src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lnitrokey -lm -largon2

mykey: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) mykey
    
