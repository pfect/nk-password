src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lnitrokey -lm

mykey: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) mykey
    
