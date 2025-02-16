import mido
import math

'''
    Designed to convert a MIDI format file into a list of notes (frequencies) and durations in miliseconds
'''
Files = [] # List of all MIDI files to be converted to list format

FileName = 'overworld.mid' # Test File
mid = mido.MidiFile(FileName, clip=True)
# print(mid)

# for track in mid.tracks:
#     print(track)

# for msg in mid.tracks[0]:
#     print(msg)

track_lists = [] # Track, pitches, lengths

for track in mid.tracks:

    pitches = []
    lengths = []
    tempo = 0
    ticks_per_beat = 0
    out_of_range = False

    for msg in track:  
        if msg.is_meta:  # Get tempo and ticks per beat from metadata
            if msg.type == 'set_tempo':
                tempo = msg.tempo
            if msg.type == 'time_signature':
                ticks_per_beat = msg.clocks_per_click
            continue
        if msg.type == 'note_on': # If there is a note, convert it to a frequency and append to the list of notes, else append a zero
            if msg.note < 48 or msg.note > 95:
                out_of_range = True
            pitches.append(math.ceil(440 * 2 ** ((msg.note - 69) / 12)))
        elif msg.type == 'note_off':
            pitches.append(0)

        if msg.time == 0:
            continue
        else:
            lengths.append(round(mido.tick2second(msg.time, ticks_per_beat, tempo) * 1000)) # Append the duration of the note in ms (rounded to the nearest whole number)


    if out_of_range:
        print("Warning: Some pitches are out of range")

    lengths.append(0)
    if len(pitches) != len(lengths):
        print("Warning: len(pitches) != len(lengths),", len(pitches), 'vs.', len(lengths))
    else:
        print("len(pitches) == len(lengths)", len(pitches), 'vs.', len(lengths))

    track_lists.append({'Track' : track, 'Pitches' : pitches, 'Lengths' : lengths, 'Duration' : sum(lengths)})

    # print('Pitches:\n')
    # print(pitches)
    # print('\nLengths:\n')
    # print(lengths)


print(track_lists)


# Message('note_on', channel=0, note=60, velocity=64, time=0)
# Board buzzers allow from C3-B6, corresponding to 48-95 in Midi
# Note values, progressing in half steps

# 440 * 2 ** (n-69) / 12
# A tick is 8 ms in MIDI
# Time represents the amount of time before the event; the length of time after the previous event at which it should be sent