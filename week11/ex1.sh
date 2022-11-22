fallocate --length 69M lofs.img
$freeloop=$(losetup -f)
sudo mkfs.ext4 $freeloop
mkdir lofsdisk
sudo mount $freeloop lofsdisk
sudo chown $USER:$USER lofsdisk
