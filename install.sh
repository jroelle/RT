if ! [ -d ~/Library ]; then
echo 'mkdir ~/Library'
mkdir ~/Library
fi

if ! [ -d ~/Library/Frameworks ]; then
echo 'mkdir ~/Library/Frameworks'
mkdir ~/Library/Frameworks
fi

echo 'installing SDL2_image.framework...'
cp -r includes/frameworks/SDL2_image.framework ~/Library/Frameworks
echo 'installing SDL2_mixer.framework...'
cp -r includes/frameworks/SDL2_mixer.framework ~/Library/Frameworks
echo 'installing SDL2_net.framework...'
cp -r includes/frameworks/SDL2_net.framework ~/Library/Frameworks
echo 'installing SDL2_ttf.framework...'
cp -r includes/frameworks/SDL2_ttf.framework ~/Library/Frameworks
echo 'installing SDL2.framework...'
cp -r includes/frameworks/SDL2.framework ~/Library/Frameworks
echo 'DONE'
