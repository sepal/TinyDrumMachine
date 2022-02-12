extern const uint8_t stealth5710x8[] PROGMEM;
const uint8_t stealth5710x8[] PROGMEM =
{
#ifdef CONFIG_SSD1306_UNICODE_ENABLE
//  type|width|height|first char
    0x01, 0x0A, 0x08, 0x20,
//  unicode(2B)|count
    0x00, 0x20, 0x60, // unicode record
#else
//  type|width|height|first char
    0x00, 0x0A, 0x08, 0x20,
#endif
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // char ' ' (0x0020/32)
    0x00, 0x00, 0x00, 0x00, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, // char '!' (0x0021/33)
    0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, // char '"' (0x0022/34)
    0x00, 0x00, 0x00, 0x00, 0x24, 0x7E, 0x24, 0x7E, 0x24, 0x24, // char '#' (0x0023/35)
    0x00, 0x00, 0x00, 0x00, 0x4E, 0x4A, 0xFF, 0x4A, 0x7A, 0x00, // char '$' (0x0024/36)
    0x00, 0x00, 0x00, 0x00, 0x46, 0x16, 0x08, 0x00, 0x74, 0x72, // char '%' (0x0025/37)
    0x00, 0x00, 0x00, 0x00, 0x76, 0x89, 0x95, 0x00, 0x42, 0x98, // char '&' (0x0026/38)
    0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // char ''' (0x0027/39)
    0x7E, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // char '(' (0x0028/40)
    0x00, 0x00, 0x00, 0x00, 0x81, 0x7E, 0x00, 0x00, 0x00, 0x00, // char ')' (0x0029/41)
    0x00, 0x00, 0x00, 0x0A, 0x04, 0x0A, 0x00, 0x00, 0x00, 0x00, // char '*' (0x002A/42)
    0x00, 0x00, 0x00, 0x10, 0x3C, 0x10, 0x10, 0x00, 0x00, 0x00, // char '+' (0x002B/43)
    0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // char ',' (0x002C/44)
    0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, // char '-' (0x002D/45)
    0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // char '.' (0x002E/46)
    0x00, 0x00, 0x00, 0x00, 0xC0, 0x10, 0x08, 0x00, 0x04, 0x03, // char '/' (0x002F/47)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x91, 0x89, 0x85, 0xFF, 0x00, // char '0' (0x0030/48)
    0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0x81, 0xFF, 0x80, 0x80, // char '1' (0x0031/49)
    0x00, 0x00, 0x00, 0x00, 0xF9, 0x89, 0x89, 0x89, 0x89, 0x8F, // char '2' (0x0032/50)
    0x00, 0x00, 0x00, 0x00, 0x89, 0x89, 0x89, 0x89, 0x89, 0xFF, // char '3' (0x0033/51)
    0x00, 0x00, 0x00, 0x00, 0x0F, 0x08, 0x08, 0x08, 0x08, 0xFF, // char '4' (0x0034/52)
    0x00, 0x00, 0x00, 0x00, 0x8F, 0x89, 0x89, 0x89, 0x89, 0xF9, // char '5' (0x0035/53)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x89, 0xF9, // char '6' (0x0036/54)
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0xF1, 0x09, 0x07, // char '7' (0x0037/55)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x89, 0xFF, // char '8' (0x0038/56)
    0x00, 0x00, 0x00, 0x00, 0x0F, 0x09, 0x09, 0x09, 0x09, 0xFF, // char '9' (0x0039/57)
    0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // char ':' (0x003A/58)
    0x00, 0x00, 0x00, 0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // char ';' (0x003B/59)
    0x00, 0x00, 0x00, 0x08, 0x14, 0x42, 0x00, 0x00, 0x00, 0x00, // char '<' (0x003C/60)
    0x00, 0x00, 0x00, 0x14, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, // char '=' (0x003D/61)
    0x00, 0x00, 0x00, 0x42, 0x14, 0x08, 0x00, 0x00, 0x00, 0x00, // char '>' (0x003E/62)
    0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x91, 0x01, 0x09, 0x06, // char '?' (0x003F/63)
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x81, 0x9D, 0x95, 0x95, 0x1E, // char '@' (0x0040/64)
    0x00, 0x00, 0x00, 0x00, 0xFE, 0x09, 0x09, 0x09, 0x09, 0xFE, // char 'A' (0x0041/65)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x89, 0x66, // char 'B' (0x0042/66)
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x42, // char 'C' (0x0043/67)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x81, 0x81, 0x81, 0x81, 0x7E, // char 'D' (0x0044/68)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x89, 0x89, 0x89, 0x89, 0x81, // char 'E' (0x0045/69)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x09, 0x09, 0x09, 0x09, 0x01, // char 'F' (0x0046/70)
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x81, 0x81, 0x81, 0x91, 0x72, // char 'G' (0x0047/71)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x08, 0x08, 0x08, 0x08, 0xFF, // char 'H' (0x0048/72)
    0x00, 0x00, 0x00, 0x00, 0x81, 0x81, 0x81, 0xFF, 0x81, 0x81, // char 'I' (0x0049/73)
    0x00, 0x00, 0x00, 0x00, 0x60, 0x80, 0x80, 0x80, 0x80, 0x7F, // char 'J' (0x004A/74)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x08, 0x14, 0x00, 0x42, 0x81, // char 'K' (0x004B/75)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, // char 'L' (0x004C/76)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x02, 0x04, 0x02, 0xFF, 0x00, // char 'M' (0x004D/77)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x02, 0x04, 0x08, 0xFF, 0x00, // char 'N' (0x004E/78)
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x7E, // char 'O' (0x004F/79)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x09, 0x09, 0x09, 0x09, 0x06, // char 'P' (0x0050/80)
    0x00, 0x00, 0x00, 0x00, 0x7E, 0x81, 0xA1, 0x01, 0x41, 0xBE, // char 'Q' (0x0051/81)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x09, 0x09, 0x09, 0x19, 0xC6, // char 'R' (0x0052/82)
    0x00, 0x00, 0x00, 0x00, 0x86, 0x89, 0x89, 0x89, 0x89, 0x61, // char 'S' (0x0053/83)
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0xFF, 0x01, 0x01, // char 'T' (0x0054/84)
    0x00, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x80, 0x80, 0x80, 0x7F, // char 'U' (0x0055/85)
    0x00, 0x00, 0x00, 0x00, 0x0F, 0x60, 0x80, 0x00, 0x60, 0x0F, // char 'V' (0x0056/86)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x40, 0x10, 0x40, 0xFF, 0x00, // char 'W' (0x0057/87)
    0x00, 0x00, 0x00, 0x00, 0xC3, 0x14, 0x08, 0x00, 0x14, 0xC3, // char 'X' (0x0058/88)
    0x00, 0x00, 0x00, 0x00, 0x87, 0x88, 0x88, 0x88, 0x88, 0x7F, // char 'Y' (0x0059/89)
    0x00, 0x00, 0x00, 0x00, 0xC1, 0x91, 0x89, 0x81, 0x85, 0x83, // char 'Z' (0x005A/90)
    0xFF, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // char '[' (0x005B/91)
    0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x00, 0x10, 0xC0, // char '\' (0x005C/92)
    0x00, 0x00, 0x00, 0x00, 0x81, 0xFF, 0x00, 0x00, 0x00, 0x00, // char ']' (0x005D/93)
    0x00, 0x00, 0x00, 0x02, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, // char '^' (0x005E/94)
    0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, // char '_' (0x005F/95)
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, // char '`' (0x0060/96)
    0x00, 0x00, 0x00, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0xFC, // char 'a' (0x0061/97)
    0x00, 0x00, 0x00, 0x00, 0xFE, 0x84, 0x84, 0x84, 0x84, 0x78, // char 'b' (0x0062/98)
    0x00, 0x00, 0x00, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x84, // char 'c' (0x0063/99)
    0x00, 0x00, 0x00, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0xFE, // char 'd' (0x0064/100)
    0x00, 0x00, 0x00, 0x00, 0x78, 0x94, 0x94, 0x94, 0x94, 0x98, // char 'e' (0x0065/101)
    0x00, 0x00, 0x00, 0x00, 0x10, 0xFC, 0x12, 0x12, 0x12, 0x12, // char 'f' (0x0066/102)
    0x00, 0x00, 0x00, 0x00, 0x1C, 0x94, 0x94, 0x94, 0x94, 0x7C, // char 'g' (0x0067/103)
    0x00, 0x00, 0x00, 0x00, 0xFC, 0x08, 0x08, 0x08, 0x08, 0xF0, // char 'h' (0x0068/104)
    0x00, 0x00, 0x00, 0x80, 0xFD, 0x80, 0x80, 0x00, 0x00, 0x00, // char 'i' (0x0069/105)
    0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x7C, // char 'j' (0x006A/106)
    0x00, 0x00, 0x00, 0x00, 0xFC, 0x10, 0x10, 0x10, 0x48, 0x84, // char 'k' (0x006B/107)
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x80, 0x80, 0x80, 0x80, 0x80, // char 'l' (0x006C/108)
    0x00, 0x00, 0x00, 0x00, 0xFC, 0x04, 0xF8, 0x04, 0xFC, 0x00, // char 'm' (0x006D/109)
    0x00, 0x00, 0x00, 0x00, 0xFC, 0x04, 0x04, 0x04, 0x04, 0xF8, // char 'n' (0x006E/110)
    0x00, 0x00, 0x00, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x78, // char 'o' (0x006F/111)
    0x00, 0x00, 0x00, 0x00, 0xFC, 0x44, 0x44, 0x44, 0x44, 0x3C, // char 'p' (0x0070/112)
    0x00, 0x00, 0x00, 0x00, 0x78, 0x44, 0x44, 0x44, 0x44, 0xFC, // char 'q' (0x0071/113)
    0x00, 0x00, 0x00, 0x00, 0xF8, 0x04, 0x04, 0x04, 0x04, 0x04, // char 'r' (0x0072/114)
    0x00, 0x00, 0x00, 0x00, 0x98, 0x94, 0x94, 0x94, 0x94, 0x34, // char 's' (0x0073/115)
    0x00, 0x00, 0x00, 0x00, 0x04, 0x7E, 0x84, 0x84, 0x84, 0x84, // char 't' (0x0074/116)
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x80, 0x80, 0x80, 0x80, 0x7C, // char 'u' (0x0075/117)
    0x00, 0x00, 0x00, 0x00, 0x3C, 0x40, 0x80, 0x00, 0x40, 0x3C, // char 'v' (0x0076/118)
    0x00, 0x00, 0x00, 0x00, 0x7C, 0x80, 0x7C, 0x00, 0x80, 0x7C, // char 'w' (0x0077/119)
    0x00, 0x00, 0x00, 0x00, 0x84, 0x48, 0x10, 0x00, 0x48, 0x84, // char 'x' (0x0078/120)
    0x00, 0x00, 0x00, 0x00, 0x8C, 0x90, 0x90, 0x90, 0x90, 0x7C, // char 'y' (0x0079/121)
    0x00, 0x00, 0x00, 0x00, 0x84, 0xC4, 0x84, 0x94, 0x8C, 0x84, // char 'z' (0x007A/122)
    0x66, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // char '{' (0x007B/123)
    0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, // char '|' (0x007C/124)
    0x00, 0x00, 0x00, 0x00, 0x89, 0x66, 0x00, 0x00, 0x00, 0x00, // char '}' (0x007D/125)
    0x00, 0x00, 0x00, 0x00, 0x04, 0x02, 0x04, 0x04, 0x00, 0x02, // char '~' (0x007E/126)
    0x00, 0x00, 0x00, 0x00, 0xFE, 0xAA, 0x92, 0xEE, 0x82, 0xFE, // char '' (0x007F/127)
#ifdef CONFIG_SSD1306_UNICODE_ENABLE
    0x00, 0x00, 0x00, // end of unicode tables
#endif
};