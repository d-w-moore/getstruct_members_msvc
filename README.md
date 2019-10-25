# iRODS - Get structure member within microservice

Beginnings of a generic structure member fetch - motivated by a need of this
facility in iRODS Native Rule Language

To compile and test-run this sample msvc:

```
cd getstruct_members_msvc
#  edit CMakeLists.txt to match current iRODS version
mkdir build
cd build
cmake ..
make
sudo install libmsiget_objstat_member.so  /usr/lib/irods/plugins/microservices/
cd build
echo "abc" >/tmp/myfile.txt; iput /tmp/myfile.txt `icd >&/dev/null; ipwd`
irule -F ../src/try_getstatmemb.r '*name="/tempZone/home/rods"'
irule -F ../src/try_getstatmemb.r '*name="/tempZone/home/rods/myfile.txt"'
``` 
