DUT = arbiter

install:
	brew install verilator
	brew install googletest

test:
	verilator -cc rtl/$(DUT).v
	verilator \
		-Wall \
		--trace \
		-cc \
		rtl/$(DUT).v \
		--exe tb/$(DUT)_tb.cpp \
		--prefix "Vdut" \
	    -CFLAGS "-fprofile-generate -fprofile-correction -I/opt/homebrew/include" \
        -LDFLAGS "-lgtest -lpthread -fprofile-generate -L/opt/homebrew/lib"

	make -j -C obj_dir -f Vdut.mk Vdut
	./obj_dir/Vdut

clean: 
	rm -rf obj_dir
	rm -rf logs
	rm -rf default_*
