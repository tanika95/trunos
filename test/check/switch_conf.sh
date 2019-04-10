
sudo dpctl unix:/tmp/s1 meter-mod cmd=add,flags=5,meter=1 drop:rate=8,burst=8
sudo dpctl unix:/tmp/s1 meter-mod cmd=add,flags=5,meter=2 drop:rate=4,burst=4
sudo dpctl unix:/tmp/s1 meter-mod cmd=add,flags=5,meter=3 drop:rate=4,burst=4
sudo dpctl unix:/tmp/s1 meter-mod cmd=add,flags=5,meter=4 drop:rate=8,burst=8

sudo dpctl unix:/tmp/s2 meter-mod cmd=add,flags=5,meter=1 drop:rate=8,burst=8
sudo dpctl unix:/tmp/s2 meter-mod cmd=add,flags=5,meter=2 drop:rate=4,burst=4
sudo dpctl unix:/tmp/s2 meter-mod cmd=add,flags=5,meter=3 drop:rate=8,burst=8
sudo dpctl unix:/tmp/s2 meter-mod cmd=add,flags=5,meter=4 drop:rate=4,burst=4

sudo dpctl unix:/tmp/s1 flow-mod table=0,cmd=add in_port=1,vlan_vid=1 meter:1 apply:output=2
sudo dpctl unix:/tmp/s1 flow-mod table=0,cmd=add in_port=1,vlan_vid=2 meter:2 apply:output=2
sudo dpctl unix:/tmp/s1 flow-mod table=0,cmd=add in_port=2,vlan_vid=3 meter:3 apply:output=1
sudo dpctl unix:/tmp/s1 flow-mod table=0,cmd=add in_port=2,vlan_vid=4 meter:4 apply:output=1

sudo dpctl unix:/tmp/s2 flow-mod table=0,cmd=add in_port=2,vlan_vid=1 meter:1 apply:output=1
sudo dpctl unix:/tmp/s2 flow-mod table=0,cmd=add in_port=2,vlan_vid=2 meter:2 apply:output=1
sudo dpctl unix:/tmp/s2 flow-mod table=0,cmd=add in_port=1,vlan_vid=3 meter:3 apply:output=2
sudo dpctl unix:/tmp/s2 flow-mod table=0,cmd=add in_port=1,vlan_vid=4 meter:4 apply:output=2
