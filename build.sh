# TODO some info about this script


# create all needed folders if not existing (local only)
if ! [ -d "build" ]; then
	mkdir build
	
	(cd build;	
		
		if ! [ -d "debug" ]; then 
			mkdir debug
		fi
		
		if ! [ -d "release" ]; then 
			mkdir release
		fi
	)
	
fi

# Build DEBUG
(cd build/debug; cmake -DCMAKE_BUILD_TYPE=Debug ../../ && make && ./talg)

# Build RLEASE
(cd build/release; cmake -DCMAKE_BUILD_TYPE=Release ../../ && make && ./talg)
