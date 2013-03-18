#!/bin/bash

echo "#!/bin/bash" > $2
echo "" >> $2
echo "cd $1/Vrep_32/; ./vrep.sh" >> $2
chmod +x $2
