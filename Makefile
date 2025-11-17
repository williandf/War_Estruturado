CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -O2

OBJ=src/main.o src/territory.o src/attack.o src/mission.o

war: $(OBJ)
	$(CC) $(CFLAGS) -o war $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) war