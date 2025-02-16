import os
import mido
import math

FileName = 'overworld.mid'
mid = mido.MidiFile(FileName, clip=True)
# print(mid)

# for track in mid.tracks:
#     print(track)

# for msg in mid.tracks[0]:
#     print(msg)

pitches = []
lengths = []
tempo = 0

for msg in mid.tracks[1]:
    if msg.is_meta: # Print metadata
        print(msg) 
        tempo = msg.tempo
    if msg.type == 'note_on': # If there is a note, convert it to a frequency and append to the list of notes, else append a zero
        pitches.append(math.ceil(440 * 2 ** ((msg.note - 69) / 12)))
    else:
        pitches.append(0)   

    # lengths.append(mido.tick2second(msg.time) / 10 ** 3) #mido.tick2second(tick, ticks_per_beat, tempo)
# print(lengths)
print(tempo)

if len(pitches) != len(lengths):
    print("Warnig: len(pitches) != len(lengths)")


# Message('note_on', channel=0, note=60, velocity=64, time=0)
# Board buzzers allow from C3-B6, corresponding to 48-95 in Midi
# Note values, progressing in half steps

# 440 * 2 ** (n-69) / 12
# A tick is 8 ms in MIDI