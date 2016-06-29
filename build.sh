# convenience in source build script for linux

# create all needed folders if not existing (local only)
if ! [ -d "bin" ]; then
	mkdir bin

	(cd bin;

		if ! [ -d "debug" ]; then
			mkdir debug
		fi

		if ! [ -d "release" ]; then
			mkdir release
		fi
	)

fi

# Build DEBUG
(cd bin/debug; cmake -DCMAKE_BUILD_TYPE=Debug ../../ && make && ./talg)

# Build RLEASE
(cd bin/release; cmake -DCMAKE_BUILD_TYPE=Release ../../ && make && ./talg)
