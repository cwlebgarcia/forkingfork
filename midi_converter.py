import mido
import math
import numpy as np


files = ['overworld.mid', 'underwater.mid', ] # List of all MIDI files to be converted to list format

# ****************************************************************************************************************************

def midi_converter(files):
    '''
    Designed to convert a MIDI format file into a list of notes (frequencies) and durations in miliseconds
    '''
    for filename in files:
        mid = mido.MidiFile(filename, clip=True)

        track_type = mid.type
        if track_type == 0: # All events merged into a single track, ex. piano
            print("Track type:", track_type)

        elif track_type == 1: # Multiple tracks are played synchronously. Tempo data is stored in the frist track by convention.
            print("Track type:", track_type)
            for msg in mid.tracks[0]:
                if msg.is_meta:
                    if msg.type == 'set_tempo':
                        tempo = msg.tempo
                    if msg.type == 'time_signature':
                        ticks_per_beat = msg.clocks_per_click

        elif track_type == 2: # Multiple independent tracks
            print("Track type:", track_type)

        else:
            print("Invalid track type (Not 0, 1, or 2)")

        track_lists = [] # Track, pitches, lengths
        max_len = -999

        for track in mid.tracks:

            pitches = [0]
            lengths = [0]

            if track_type != 1: # Synchronize tempo across tracks for type 1 
                tempo = 0
                ticks_per_beat = math.inf

            out_of_range = False

            for msg in track:  
                if msg.is_meta:  # Get tempo and ticks per beat from metadata
                    if track_type != 1:
                        if msg.type == 'set_tempo':
                            tempo = msg.tempo
                        if msg.type == 'time_signature':
                            ticks_per_beat = msg.clocks_per_click
                    continue
                
                if msg.type == 'note_off' : 
                    pitches.append(0)
                elif msg.type == 'note_on': # If there is a note, convert it to a frequency and append to the list of notes, else append a zero
                    if msg.velocity == 0:
                        pitches.append(0)
                    else:
                        pitches.append(math.ceil(440 * 2 ** ((msg.note - 69) / 12)))
                    if msg.note < 48 or msg.note > 95:
                        out_of_range = True
                    

                if msg.time == 0:
                    continue
                elif msg.time > 0:
                    lengths.append(round(mido.tick2second(msg.time, ticks_per_beat, tempo) * 1000)) # Append the duration of the note in ms (rounded to the nearest whole number)
                else:
                    print('Might be cooked')
            

            if out_of_range:
                print(track, "Warning: Some pitches are out of range")

            lengths.append(0)
            if len(pitches) != len(lengths):
                print(track, "Warning: len(pitches) != len(lengths)", len(pitches), 'vs.', len(lengths),)
            else:
                print(track, "len(pitches) == len(lengths)", len(pitches), 'vs.', len(lengths),)
            
            # if len(lengths) > max_len:
            #     max_len = len(lengths)
            
            # if len(lengths) < max_len:
                # np.resize(lengths, )


            track_lists.append({'Track' : track, 'Pitches' : pitches, 'Lengths' : lengths, 'Duration' : sum(lengths)})


        [print('\n', i, '\n') for i in track_lists]

# ****************************************************************************************************************************

def track_viewer(filename):
    mid = mido.MidiFile(filename, clip=True)
    print(mid)
    for track in mid.tracks:
        print(track ,'\n')
        for msg in track:
            print(msg)

# ****************************************************************************************************************************

def read_meta(filename):
    mid = mido.MidiFile(filename, clip=True)
    print(mid)
    for track in mid.tracks:
        print(track ,'\n')
        for msg in track:
            if msg.is_meta:
                print(msg)


# ****************************************************************************************************************************

track_viewer('Wii Channels - Mii Channel.mid')
# midi_converter(['Wii Channels - Mii Channel.mid'])
read_meta('Wii Channels - Mii Channel.mid')

# track_viewer('overworld.mid')
# midi_converter(['overworld.mid'])
# read_meta('overworld.mid')

# ****************************************************************************************************************************

# Message('note_on', channel=0, note=60, velocity=64, time=0)
# Board buzzers allow from C3-B6, corresponding to 48-95 in Midi
# Note values, progressing in half steps

# 440 * 2 ** (n-69) / 12
# A tick is 8 ms in MIDI
# Time represents the amount of time before the event; the length of time after the previous event at which it should be sent