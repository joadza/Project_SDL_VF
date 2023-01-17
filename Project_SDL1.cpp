// SDL_Test.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "Project_SDL1.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <numeric>
#include <random>
#include <string>

void init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO) < 0)
    throw std::runtime_error("init():" + std::string(SDL_GetError()));

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags))
    throw std::runtime_error("init(): SDL_image could not initialize! "
                             "SDL_image Error: " +
                             std::string(IMG_GetError()));
}

namespace {
// Defining a namespace without a name -> Anonymous workspace
// Its purpose is to indicate to the compiler that everything
// inside of it is UNIQUELY used within this source file.

SDL_Surface* load_surface_for(const std::string& path,
                              SDL_Surface* window_surface_ptr) {

  // Load image at specified path
  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == nullptr)
    throw std::runtime_error("load_surface_for(): Unable to load image " +
                             path + "! SDL_image Error: " +
                             std::string(IMG_GetError()));
    return loaded_surface; 

}






} // namespace


/***** Object *****/
object::object(SDL_Surface* window_surface_ptr)
    : window_surface_ptr_(window_surface_ptr) {
  
}

void object::set_x(int x) { this->x = x; }
void object::set_y(int y) { this->y = y; }
int object::get_x() const { return x; }
int object::get_y() const { return y; }
void object::set_shape_size(int shape_size) { this->shape_size = shape_size; }
void object::set_type(Type type) { this->type = type; }
Type object::get_type() const { return type; }

void object::add_character(std::shared_ptr<object> character_ptr) {
  characters.push_back(character_ptr);
}

void object::move(){
  std::cout << "Moving object" << std::endl;
}

void object::draw(SDL_Surface *window_surface_ptr, SDL_Surface *image_surface_ptr) {
  // Blit the surface
  //display x and y  

  SDL_Rect stretch_rect;
  stretch_rect.x = x;
  stretch_rect.y = y;
  stretch_rect.w = shape_size;
  stretch_rect.h = shape_size;
  if(get_type() == BACKGROUND)
    SDL_BlitSurface(image_surface_ptr, NULL, window_surface_ptr, &stretch_rect);
  else
    SDL_BlitScaled(image_surface_ptr, NULL, window_surface_ptr, &stretch_rect);
}

std::vector<std::shared_ptr<object>> object::get_characters() const {
  return characters;
}



void object::set_image_ptr(SDL_Surface* image_ptr) {
  this->image_ptr_ = image_ptr;
}

SDL_Surface* object::get_image_ptr() const { return image_ptr_; }

/*######## object ########*/

/***** Moving Object ***********/

object* object::get_nearest_object(Type type)
{
  int min_distance = 100000;
  object* nearest_object = nullptr;
  
  //print firts character


  for(auto character = characters.begin(); character != characters.end(); ++character)
  {
    if((*character)->get_type() == type)
    {
      int distance = sqrt(pow((*character)->get_x() - x, 2) + pow((*character)->get_y() - y, 2));
      if(distance < min_distance)
      {
        min_distance = distance;
        nearest_object = (*character).get();
      }
    }
  }

  return nearest_object;
}




moving_object::moving_object(SDL_Surface* window_surface_ptr)
    : object(window_surface_ptr) {
    
}

void moving_object::set_speed(float speed) { this->speed = speed; }
void moving_object::set_direction_x(float direction_x) {
  this->direction_x = direction_x;
}

void moving_object::set_direction_y(float direction_y) {
  this->direction_y = direction_y;
}

float moving_object::get_speed() const { return speed; }
float moving_object::get_direction_x() const { return direction_x; }
float moving_object::get_direction_y() const { return direction_y; }


/*########### Moving object ###########*/

/***** NON Moveable Object *****/
non_moveable_object::non_moveable_object(const std::string& file_path,
                                         SDL_Surface* window_surface_ptr)
    : object(window_surface_ptr) {
    
}


/*########### NON Moveable Object ###########*/

/***** Background *****/
background::background(const std::string& file_path,
                       SDL_Surface* window_surface_ptr)
    :non_moveable_object(file_path, window_surface_ptr) {
    set_x(0);
    set_y(0);
    set_shape_size(0);
    set_type(BACKGROUND);
    image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    if (image_ptr_ == nullptr)
      throw std::runtime_error("background(): Unable to load image " + file_path +
                               "! SDL_image Error: " + std::string(IMG_GetError()));
    else
      std::cout << "Background loaded successfully" << std::endl;
}

background::~background() {
  SDL_FreeSurface(image_ptr_);
}

SDL_Surface* background::get_image_ptr() const {
  return image_ptr_;
}



/*########### Background ###########*/

/****** Animal ****/
animal::animal(const std::string& file_path, SDL_Surface* window_surface_ptr)
    : moving_object(window_surface_ptr) {

    
}

void animal::set_alive(bool alive) { this->alive = alive; }
bool animal::get_alive() const { return alive; }

/*####### Animal ######*/

/***** Sheep *****/
sheep::sheep(const std::string& file_path, SDL_Surface* window_surface_ptr)
    : animal(file_path, window_surface_ptr) {
    set_x(rand() % (TAILLE_MAX_X - TAILLE_MIN_X) + TAILLE_MIN_X);
    set_y(rand() % (TAILLE_MAX_Y - TAILLE_MIN_Y) + TAILLE_MIN_Y);
    set_shape_size(60);
    set_speed(2);
    set_direction_x(rand() % 1000);
    set_direction_y(rand() % 1000);
    set_alive(true);
    set_type(SHEEP);
    set_image_ptr(load_surface_for(file_path, window_surface_ptr));
    if (rand() % 2 == 1)
        sexe = MALE;
    else
        sexe = FEMELLE;
    //image_ptr_ = load_surface_for(file_path, window_surface_ptr);
    if (get_image_ptr() == nullptr)
      throw std::runtime_error("sheep(): Unable to load image " + file_path +
                               "! SDL_image Error: " + std::string(IMG_GetError()));
    else
      std::cout << "Sheep loaded successfully" << std::endl;

    std::cout << get_image_ptr() << std::endl;
}

void sheep::move() {
  std::cout << "object_ptr_ : " << get_characters().size() << std::endl;
  
  float temp_taux = 0.1;

  if(get_x() < TAILLE_MIN_X)
    set_direction_x(rand() % 1000);
  else if(get_x() > TAILLE_MAX_X)
    set_direction_x(-rand() % 1000);
  if(get_y() < TAILLE_MIN_Y)
    set_direction_y(rand() % 1000);
  else if(get_y() > TAILLE_MAX_Y)
    set_direction_y(-rand() % 1000);
  temp_taux = sqrt(pow(get_direction_x(), 2) + pow(get_direction_y(), 2));
  set_x(get_x() + get_direction_x() * get_speed() / temp_taux);
  set_y(get_y() + get_direction_y() * get_speed() / temp_taux);

}




/*######  Sheep ######*/


/***** Wolf *****/
wolf::wolf(const std::string& file_path, SDL_Surface* window_surface_ptr)
    : animal(file_path, window_surface_ptr) {
    set_x(rand()%SCREEN_WIDTH);
    set_y(10);
    set_speed(3);
    set_direction_x(0);
    set_direction_y(0);
    set_alive(true);
    set_shape_size(70);
    set_type(WOLF);
    set_image_ptr(load_surface_for(file_path, window_surface_ptr));
    if (get_image_ptr() == nullptr)
      throw std::runtime_error("wolf(): Unable to load image " + file_path +
                               "! SDL_image Error: " + std::string(IMG_GetError()));
    else
      std::cout << "Wolf loaded successfully" << std::endl;
    }

void wolf::move(){

  object * neareast = get_nearest_object( SHEEP);
  if(neareast != nullptr){
    float temp_taux = 0.1;
    set_direction_x(neareast->get_x() - get_x());
    set_direction_y(neareast->get_y() - get_y());
    temp_taux = sqrt(pow(get_direction_x(), 2) + pow(get_direction_y(), 2));
    set_x(get_x() + get_direction_x() * get_speed() / temp_taux);
    set_y(get_y() + get_direction_y() * get_speed() / temp_taux);
  }
  else
  {
    set_x(50);
    set_y(50);
  }


}
  
/*###### Wolf ######*/



/*** Application *****/
application::application(unsigned n_sheep, unsigned n_wolf)
{
  // Create window
  window_ptr_ = SDL_CreateWindow("SDL Project", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                 SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window_ptr_ == nullptr)
    throw std::runtime_error("application(): Window could not be created! "
                             "SDL_Error: " +
                             std::string(SDL_GetError()));

  window_surface_ptr_ = SDL_GetWindowSurface(window_ptr_);
  SDL_FillRect(window_surface_ptr_, NULL, SDL_MapRGB(window_surface_ptr_->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(window_ptr_);

  object_ptr_ = new object(window_surface_ptr_);


  // Load sheep
  
  for (unsigned i = 0; i < n_sheep; ++i) {
    object_ptr_->add_character(std::make_shared<sheep>("images/sheep.png", window_surface_ptr_));
  }



  // Load wolf
  
  for (unsigned i = 0; i < n_wolf; ++i) {
    object_ptr_->add_character(std::make_shared<wolf>("images/wolf.png", window_surface_ptr_));
  }
}

application::~application() {
  SDL_FreeSurface(window_surface_ptr_);
  SDL_DestroyWindow(window_ptr_);
  SDL_Quit();
}
void object::update() {
  // Move all animals
  for (auto& character : characters) {
    character->move();
    character->draw(window_surface_ptr_, character->get_image_ptr());
  }
}

int application::loop(unsigned period) {
  // Event handler
  SDL_Event e;
  srand(time(NULL));
  
  background * background_ptr_ =  new background("images/background.png", window_surface_ptr_);
 

  // While application is running
  bool quit = false;

  //printobject(object_ptr_->get_characters());




  while (!quit) {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    //draw background
    background_ptr_->draw(window_surface_ptr_, background_ptr_->get_image_ptr());

    // Update
    //disply first element of object_ptr

    object_ptr_->update();

    // Update the surface
    SDL_UpdateWindowSurface(window_ptr_);

    // Wait
    SDL_Delay(period);
  }

  return 0;
}