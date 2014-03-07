/*
Poor Man's Telnet - a tiny Galileo/Arduino sketch to talk to the 
Galileo underlying Linux command line.
By Mikal Hart

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

char buf[1024];
int offset = 0;
const char redirect[] = " &>/dev/ttyGS0 &";
const int MAXLINE = sizeof(buf) - sizeof(redirect) - 1;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == '\r')
    {
      Serial.println();
      if (offset >= MAXLINE)
      {
        Serial.println("Too many characters in line");
      }
      else
      {
        buf[offset] = 0;
        strcat(buf, redirect);
        system(buf);
      }
      offset = 0;
    }
    else
    {
      if (offset < MAXLINE)
        buf[offset++] = c;
      Serial.write(c);
    }
  }
}
