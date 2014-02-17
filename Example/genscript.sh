#!/bin/bash

echo "#!/bin/bash" > $2
echo "" >> $2
echo "cd $1/Vrep/; ./vrep.sh" >> $2
chmod +x $2
