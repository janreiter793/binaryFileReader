/* A small program that can read a binary file to console. It reads
 * data to console byte by byte and displays each byte as a hex-value.
 */
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cctype>

// Function for printing a byte as a hex
void printByteAsHex(char ch);

int main(int argc, char *argv[]) {
  // Check for appropriate parameters
  if(argc != 2) {
    std::cout << "Please specify one binary file to read.\n";
    return 1;
  }

  // Try to open the file
  std::ifstream in(argv[1], std::ios::binary);
  if(!in) {
    std::cout << "Could not open the specified file.\n";
    return 1;
  }

  // Display the contents of the file
  size_t bytenum = 0; // Used for counting each byte
  char ch; // The byte
  char line[16];
  while(in.get(ch)) {
    if((bytenum % 16) == 0) {
      std::cout << std::hex << std::setw(8) <<
        std::setfill('0') << bytenum << " : ";
    }

    printByteAsHex(ch);  
    line[bytenum % 16] = ch;

    std::cout << " ";
    if((bytenum % 16) == 7) {
      std::cout << " ";
    }

    if((bytenum % 16) == 15) {
      std::cout << "  ";
      for(size_t t = 0; t < 8; t++) {
        if(isprint(static_cast<unsigned char>(line[t]))) {
          std::cout << line[t];
        } else {
          std::cout << ".";
        }
      }
      std::cout << " ";
      for(size_t t = 8; t < 16; t++) {
        if(isprint(static_cast<unsigned char>(line[t]))) {
          std::cout << line[t];
        } else {
          std::cout << ".";
        }

      }
      std::cout << "\n";
    }

    bytenum++;
  }

  // Pad the the missing bytes and add the final line of text
  size_t paddingbytes = bytenum;
  while(bytenum % 16) {
    std::cout << "   ";
    if((bytenum % 16) == 7) {
      std::cout << " ";
    }
    bytenum++;
  }
  std::cout << "  ";
  for(size_t t = 0; (t < 8) && (t < (paddingbytes % 16)); t++) {
    if(isprint(static_cast<unsigned char>(line[t]))) {
      std::cout << line[t];
    } else {
      std::cout << ".";
    }
  }
  std::cout << " ";
  for(size_t t = 8; (t < 16) && (t < (paddingbytes % 16)); t++) {
    if(isprint(static_cast<unsigned char>(line[t]))) {
      std::cout << line[t];
    } else {
      std::cout << ".";
    }

  }
  
  std::cout << "\n";
  return 0;
}

// This function prints a character used for storing a byte as a hex
void printByteAsHex(char ch) {
  // Index the digits of the hex-scale
  const static char hex_digits[] = "0123456789ABCDEF";  

  unsigned char b = static_cast<unsigned char>(ch);
  // First print the first four digits
  std::cout << hex_digits[(b >> 4) & 0x0F];

  // Print the final four digits
  std::cout << hex_digits[b & 0x0F];
}
