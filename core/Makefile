TARGET := $(shell pwd)/module.a
SRCS := comm.c common.c interrupt.c main.c scheduler.c sync.c task.c timer.c
OBJS := $(patsubst %.c,%.o,$(SRCS))

# compling and linking this directory
$(TARGET): banner $(OBJS)
ifneq ($(OBJS),)
	ar r $@ $(filter-out banner, $^)
endif

banner:
	@echo ----------------------------------------------------
	@echo Compiling in $(shell pwd)
	@echo ----------------------------------------------------

%.o: %.c
	$(CC) -c -Os -Wall -D_KERNEL_ -I$(HPATH) -o $@ $< 

clean_:
	rm -rf $(TARGET) $(OBJS)
