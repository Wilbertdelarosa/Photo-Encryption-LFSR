#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"

void transfrom(sf::Image &image,sf::Image &encryPimage, FibLFSR *lfsr) {
	auto size = image.getSize();
	  encryPimage.create(size.x,size.y);
	  sf::Color p;
	  
	  for (unsigned int x = 0; x<size.x; x++) {
	    for (unsigned int y = 0; y< size.y; y++) {
	      p = image.getPixel(x, y);
	      p.r ^= lfsr->generate(8);
	      p.g ^= lfsr->generate(8);
	      p.b ^= lfsr->generate(8);
	      encryPimage.setPixel(x, y, p);
	    }
	  }
}

int main(int argc, char** args)
{
  if(argc != 5) {
    return EXIT_FAILURE;
  }
  char* infile = args[1];
  char* outfile = args[2];

  std::string seed(args[3]);
  

  int tap = 0;
  for(char* str = args[4]; *str; str++) {
    tap = tap*10 + *str-'0';
  }
  
  FibLFSR lfsr(seed,tap);

  sf::Image image;
  sf::Image encryPimage;

  if (!image.loadFromFile(infile)){
	return -1;
   }
    

  transfrom(image,encryPimage, &lfsr);
  auto size = image.getSize();
 
  sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "encode");
  sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "decode");

  sf::Texture texture1;
  texture1.loadFromImage(image);

  sf::Sprite sprite1;
  sprite1.setTexture(texture1);

  sf::Texture texture2;
  texture2.loadFromImage(encryPimage);

  sf::Sprite sprite2;
  sprite2.setTexture(texture2);

  while (window1.isOpen() && window2.isOpen()) {
    sf::Event event;
    while (window1.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window1.close();
    }
    while (window2.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window2.close();
    }
    window1.clear();
    window1.draw(sprite1);
    window1.display();
    window2.clear();
    window2.draw(sprite2);
    window2.display();
  }

  if (!encryPimage.saveToFile(outfile))
    return -1;

  return 0;
}
