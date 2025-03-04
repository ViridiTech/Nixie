# Nixie
 4 digit nixie clock on IN-12 lamps
 
<img src="pics/overview.png" width="800px"></a>

General schematic inculed most important components:

<img src="pics/gen schematic.png" width="800px"></a>

Brain of the clock is [ESP32-C3 Super Mini](https://allegro.pl/events/clicks?emission_unit_id=f06a5ec8-8059-49f5-b3e1-0427a0f30828&emission_id=fa8220df-9dc3-44b3-8bd5-d7bab4bfcdd1&type=OFFER&ts=1741079374214&redirect=https%3A%2F%2Fallegro.pl%2Foferta%2Fesp32-c3-super-mini-wifi-bluetooth-ble-5-0-nastepca-esp8266-d1-mini-15295513744%3Fbi_s%3Dads%26bi_m%3Dproductlisting%253Adesktop%253Aquery%26bi_c%3DYjM1MWQ2YjgtZmRkYS00ZTU5LWE4YWEtZmFkNTI4YTliM2E3AA%26bi_t%3Dape&placement=productlisting:desktop:query&sig=47fc114a77d64e92962a4eec50b8c331).

ICs used:

- two 74HC959 shift registers,

- four nixie lamp drivers: K155ID1 and SN74141N both work the same and have the same I/O.

Four IN-12 display time. Both A and B variants could be used.

Seconds indicator is taken from probe screwdriver, typical neon indicator (gas-discharge lamp) can be used.

Seconds indicator is driven by 5V relay (transistor-diode control to ensure no damage to microcontroler should be used, or alternatively for DIY solution Arduino relay module can be used).

Nixie lamps require 170V power supply to be used, I chose [this one](https://pl.aliexpress.com/item/1005005721193065.html?src=google&pdp_npi=4%40dis!PLN!15.17!11.59!!!!!%40!12000034113964492!ppc!!!&src=google&albch=shopping&acnt=708-803-3821&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&gclsrc=aw.ds&&albagn=888888&&ds_e_adid=&ds_e_matchtype=&ds_e_device=c&ds_e_network=x&ds_e_product_group_id=&ds_e_product_id=pl1005005721193065&ds_e_product_merchant_id=107726890&ds_e_product_country=PL&ds_e_product_language=pl&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&albcp=19735245762&albag=&isSmbAutoCall=false&needSmbHouyi=false&gad_source=1&gclid=CjwKCAiA5pq-BhBuEiwAvkzVZf3OkaujjkBrAG5RaLtoEE9kd9NwcMxYW9DeDCp0z5XIMhVfqe0_oxoCYh0QAvD_BwE).
