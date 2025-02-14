import os
import mido

mid = MidiFile(FileName, clip=True)

notes = []

num_to_note = {}

for track in mido.tracks(mid):
    for msg in track:
        if msg[0] == 'note_on':
            notes[msg] =  [int(num) for num in msg[2]] 

# Message('note_on', channel=0, note=60, velocity=64, time=0)
# Board buzzers allow from C3-B6, corresponding to 48-95 in Midi
# Note values, progressing in half steps

# 440 * 2 ^ (n-69) / 12