#include <Keypad.h>
#include <Joystick.h>
#include <Rotary.h>

#define ENABLE_PULLUPS
#define NUMROTARIES 4
#define NUMBUTTONS 24
#define NUMROWS 4
#define NUMCOLS 4

byte buttons[NUMROWS][NUMCOLS] =
{
  {0,1,2,3},
  {4,5,6,7},
  {8,9,10,11},
  {12,13,14,15}
};
byte rowPins[NUMROWS] = {21,20,19,18};
byte colPins[NUMCOLS] = {15,14,16,10};

Keypad buttbx = Keypad( makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS);

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                    JOYSTICK_TYPE_GAMEPAD, NUMBUTTONS, 0,
                    false, false, false, false, false, false,
                    false, false, false, false, false);

void setup()
{
  Joystick.begin();
}

void loop()
{
  CheckAllEncoders();
  CheckAllButtons();
}

void CheckAllButtons(void)
{
  if (buttbx.getKeys())
  {
    for (int i=0; i<LIST_MAX; i++)
    {
      if ( buttbx.key[i].stateChanged )
      {
        switch (buttbx.key[i].kstate)
        {
          case PRESSED:
          case HOLD:
            //Joystick.setButton(buttbx.key[i].kchar, 1);
            Joystick.pressButton(buttbx.key[i].kchar);
            break;
          case RELEASED:
          case IDLE:
            //Joystick.setButton(buttbx.key[i].kchar, 0);
            Joystick.releaseButton(buttbx.key[i].kchar);
            break;
        }
      }
    }
  }
}

Rotary rotarys[NUMROTARIES] =
{
  Rotary(0, 1),
  Rotary(2, 3),
  Rotary(4, 5),
  Rotary(6, 7)
};

byte rotaryButtonNum[NUMROTARIES][2] = {
  {16,17},
  {18,19},
  {20,21},
  {22,23}
};

void CheckAllEncoders(void)
{
  for(int i=0; i<NUMROTARIES; i++)
  {
    unsigned char result = rotarys[i].process();
    if (result == DIR_CCW)
    {
      Joystick.pressButton(rotaryButtonNum[i][0]);
      delay(100);
      Joystick.releaseButton(rotaryButtonNum[i][0]);
    };

    if (result == DIR_CW)
    {
      Joystick.pressButton(rotaryButtonNum[i][0]);
      delay(100);
      Joystick.releaseButton(rotaryButtonNum[i][0]);
    };

  }
}
