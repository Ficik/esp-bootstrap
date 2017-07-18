MONITOR="pio serialports monitor"

deploy: build
	 pio run --target upload

website:
	bash bin/compile_assets.sh;

build: website
	pio run;

monitor: ; $MONITOR
