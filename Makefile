ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
$(eval $(ARGS):;@:)

.DEFAULT_GOAL := build

BUILD_TYPE := Debug
BUILD_TYPE_LC := $(shell BT=$(BUILD_TYPE); echo $${BT} | tr '[:upper:]' '[:lower:]')
BUILD_DIR := cmake-build-${BUILD_TYPE_LC}

.PHONY: bootstrap
bootstrap:
	git submodule update --init && vcpkg/bootstrap-vcpkg.sh

.PHONY: clean
clean:
	rm -rf ${BUILD_DIR}

.PHONY: configure
configure:
	cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -G Ninja -S . -B ${BUILD_DIR}

.PHONY: build
build:
	@cmake --build ${BUILD_DIR}

.PHONY: runSample1
runSample1: build
	@${BUILD_DIR}/sample/sample1 $(ARGS)

.PHONY: reconfigure
reconfigure: clean configure