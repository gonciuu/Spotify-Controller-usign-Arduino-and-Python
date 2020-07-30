import serial
import time
from SwSpotify import spotify
from pynput.keyboard import Key, Controller

ser = serial.Serial('COM3', 9600)
keyboard = Controller()


while True:
   try:
      title, artist = spotify.current()
      ser.write(title.encode())
      ser.write('^'.encode())
      ser.write(artist.encode())
   except:
      ser.write("music paused".encode())
   time.sleep(0.410)
   if ser.inWaiting():
      action = ser.readline()
      if action == b'>>|\r\n':
         keyboard.press(Key.media_next)
      elif action == b'|<<\r\n':
         keyboard.press(Key.media_previous)
      elif action == b'+\r\n':
         keyboard.press(Key.media_volume_up)
      elif action == b'-\r\n':
         keyboard.press(Key.media_volume_down)
      elif action == b'>|\r\n':
         keyboard.press(Key.media_play_pause)
      elif action == b'EQ\r\n':
         keyboard.press(Key.media_volume_mute)
      print(action)


   
