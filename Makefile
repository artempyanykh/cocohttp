ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
$(eval $(ARGS):;@:)

.DEFAULT_GOAL := build

BUILD_TYPE := debug
BUILD_DIR := cmake-build-${BUILD_TYPE}

.PHONY: bootstrap
bootstrap:
	git submodule update --init && vcpkg/bootstrap-vcpkg.sh

.PHONY: clean
clean:
	rm -rf ${BUILD_DIR}

.PHONY: configure
configure:
	cmake -S . -B ${BUILD_DIR} -G Ninja -DCMAKE_BUILD_TYPE=${BUILD_TYPE}

.PHONY: build
build:
	@cmake --build ${BUILD_DIR}

.PHONY: runSample1
runSample1: build
	@${BUILD_DIR}/sample/sample1 $(ARGS)

.PHONY: reconfigure
reconfigure: clean configure