# matrix keyboard
tipke = [['1', '2', '3', 'A'],
         ['4', '5', '6', 'B'],
         ['7', '8', '9', 'C'],
         ['*', '0', '#', 'D']]

# pinovi na koje je povezana
keypad_rows = [21, 22, 26, 27]
keypad_cols = [0, 1, 2, 3]

# prazni nizovi u koje će se dodijeliti Pin(i, Pin.IN/OUT)
col_pins = []
row_pins = []

# dodjela fizickih pinova
for x in range(0,4):
  row_pins.append(Pin(keypad_rows[x], Pin.OUT))
  row_pins[x].value(1)
  col_pins.append(Pin(keypad_cols[x], Pin.IN, Pin.PULL_DOWN))
  col_pins[x].value(0)

# scankeys() - vraca char koji je procitan s tastature 
def scankeys():
  for row in range(4):
    for col in range(4):
      row_pins[row].high()
      key = None

      if col_pins[col].value() == 1:
        print("Tipka: ", tipke[row][col])
        key_press = tipke[row][col]
        return key_press
        time.sleep(0.3)
    
    row_pins[row].low()
  return None
