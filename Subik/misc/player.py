import ogg.vorbis 
import ao  
filename = '/home/subzero/MyMusic/hypocrisy - catch 22/07 Hatred.ogg' 

device = 'arts'#'alsa' 
SIZE = 4096 
vf = ogg.vorbis.VorbisFile(filename) 
id = ao.driver_id(device) 
ao = ao.AudioDevice(id) 
while 1:
    (buff, bytes, bit) = vf.read(SIZE)
    if bytes == 0: 
         break
    ao.play(buff, bytes)     
 
