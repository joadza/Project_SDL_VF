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

void object::move(std::vector<std::shared_ptr<object>> characters) {
 
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

int object::distance(object* object) {
  return sqrt(pow(object->get_x() - x, 2) + pow(object->get_y() - y, 2));
}

bool object::is_alive() { return alive; }
void object::set_alive(bool alive_) { alive = alive_; }

object * object::get_characters_by_type(Type type, std::vector<std::shared_ptr<object>> characters) {
  for (auto character = characters.begin(); character != characters.end(); ++character) {
    if ((*character)->get_type() == type) {
      return (*character).get();
    }
  }
  return nullptr;
}

int object::get_shape_size() const { return shape_size; }



object* object::get_nearest_object(Type type, std::vector<std::shared_ptr<object>> characters)
{
  int min_distance = 100000;
  object* nearest_object = nullptr;

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


void object::set_is_hunting(bool is_hunting_) {
  is_hunting = is_hunting_;
}

bool object::get_is_hunting() const {
  return is_hunting;
}

void object::set_go_hunt(bool go_hunt) {
  is_go_hunt = go_hunt;
}

bool object::get_go_hunt() const {
  return is_go_hunt;
}

void object::set_x_hunt(int x_hunt_) {
  x_hunt = x_hunt_;
}

int object::get_x_hunt() const {
  return x_hunt;
}

void object::set_y_hunt(int y_hunt_) {
  y_hunt = y_hunt_;
}

int object::get_y_hunt() const {
  return y_hunt;
}

void object::set_direction_x(float direction_x) {
  this->direction_x = direction_x;
}

void object::set_direction_y(float direction_y) {
  this->direction_y = direction_y;
}
float object::get_direction_x() const { return direction_x; }
float object::get_direction_y() const { return direction_y; }



/*######## object ########*/

/***** Moving Object ***********/





moving_object::moving_object(SDL_Surface* window_surface_ptr)
    : object(window_surface_ptr) {
    
}

void moving_object::set_speed(float speed) { this->speed = speed; }

float moving_object::get_speed() const { return speed; }


/*########### Moving object ###########*/

/***** NON Moveable Object *****/
non_moveable_object::non_moveable_object(const std::string& file_path,
                                         SDL_Surface* window_surface_ptr)
    : object(window_surface_ptr) {
    
}


/*########### NON Moveable Object ###########*/

/***** Playable Character *****/


playable_character::playable_character(const std::string& file_path, SDL_Surface* window_surface_ptr)
    : moving_object(window_surface_ptr) {

}

playable_character::~playable_character() {

}




/******** shepherd ********/

shepherd::shepherd(const std::string& file_path, SDL_Surface* window_surface_ptr)
    : playable_character(file_path, window_surface_ptr) {
  set_x(500);
  set_y(500);
  set_shape_size(100);
  set_type(SHEPHERD);
  set_alive(true);
  set_image_ptr(load_surface_for(file_path, window_surface_ptr));
  if (get_image_ptr() == nullptr)
    throw std::runtime_error("shepherd(): Unable to load image " + file_path +
                             "! SDL_image Error: " + std::string(IMG_GetError()));
  else
    std::cout << "shepherd(): Image " << file_path << " loaded successfully!" << std::endl;
}

shepherd::~shepherd() {
    SDL_FreeSurface(image_ptr_);
  }

void shepherd::handle_event(SDL_Event& e) {
  //If a key was pressed
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    //Adjust the velocity
    switch (e.key.keysym.sym) {
    case SDLK_z: set_direction_y(-1); break;
    case SDLK_s: set_direction_y(1); break;
    case SDLK_q: set_direction_x(-1); break;
    case SDLK_d: set_direction_x(1); break;
    }
  }
  //If a key was released
  else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
    //Adjust the velocity
    switch (e.key.keysym.sym) {
    case SDLK_z: set_direction_y(0); break;
    case SDLK_s: set_direction_y(0); break;
    case SDLK_q: set_direction_x(0); break;
    case SDLK_d: set_direction_x(0); break;
    }
  }
}
/*###### shepherd #########*/





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

/***** shepherd_dog *****/



shepherd_dog::shepherd_dog(const std::string& file_path, SDL_Surface* window_surface_ptr,int i)
    : animal(file_path, window_surface_ptr) {
  set_x(500);
  set_y(500);
  set_shape_size(60);
  set_type(SHEPHERD_DOG);
  set_alive(true);
  set_speed(SPEED_DOG);

  angle = (6.2831/NB_SHEPHERD_DOG) * (i+1); 

  //put angle in fonction of number of shepherd dog



  std::cout << "raduis = " << rand()%360 << std::endl;
  std::cout << "shepherd_dog(): angle = " << get_angle() << std::endl;
  set_is_hunting(false);


  set_image_ptr(load_surface_for(file_path, window_surface_ptr));
  if (get_image_ptr() == nullptr)
    throw std::runtime_error("shepherd_dog(): Unable to load image " + file_path +
                             "! SDL_image Error: " + std::string(IMG_GetError()));
  else
    std::cout << "shepherd_dog(): Image " << file_path << " loaded successfully!" << std::endl;
}

shepherd_dog::~shepherd_dog() {
  SDL_FreeSurface(get_image_ptr());
}

void shepherd_dog::set_angle(float angle_m) {
  angle = angle_m;
}

float shepherd_dog::get_angle() const {
  return angle;
}


void shepherd_dog::move(std::vector<std::shared_ptr<object>> characters)
{

  
  object * shepherd = get_characters_by_type(SHEPHERD, characters);

  float tmp_speed = 0.02;
  float temp_taux = 0.1;
  set_angle(get_angle() + ORBIT_SPEED);
  if (get_is_hunting())
  {
    
    if(get_go_hunt())
    {
      set_direction_x(get_x_hunt() - get_x());
      set_direction_y(get_y_hunt() - get_y());
    }
    else
    {
      set_direction_x(shepherd->get_x() + cos(get_angle()) * ORBIT_RADIUS - get_x());
      set_direction_y(shepherd->get_y() + sin(get_angle()) * ORBIT_RADIUS - get_y());
    }
    if(get_x() > get_x_hunt() - 10 && get_x() < get_x_hunt() + 10 && get_y() > get_y_hunt() - 10 && get_y() < get_y_hunt() + 10)
    {
        set_go_hunt(false);

    }
    if(!get_go_hunt() && get_x() > shepherd->get_x() + cos(get_angle()) * ORBIT_RADIUS - 10 && get_x() < shepherd->get_x() + cos(get_angle()) * ORBIT_RADIUS + 10 && get_y() > shepherd->get_y() + sin(get_angle()) * ORBIT_RADIUS - 10 && get_y() < shepherd->get_y() + sin(get_angle()) * ORBIT_RADIUS + 10)
    {
        set_is_hunting(false);
    }

    temp_taux = sqrt(pow(get_direction_x(), 2) + pow(get_direction_y(), 2));
    set_x(get_x() + get_speed() * get_direction_x() / temp_taux);
    set_y(get_y() + get_speed() * get_direction_y() / temp_taux);

  }
  else
  {
    set_x(shepherd->get_x()+shepherd->get_shape_size()/4 + cos(get_angle()) * ORBIT_RADIUS);
    set_y(shepherd->get_y()+ shepherd->get_shape_size()/4 + sin(get_angle()) * ORBIT_RADIUS);

  }


}


/*######## shepherd_dog ########*/

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

sheep::~sheep() {
  SDL_FreeSurface(get_image_ptr());
}

void sheep::move(std::vector<std::shared_ptr<object>> characters) {
 
 
  object *nearest_wolf = get_nearest_object(WOLF, characters);
  //transforme nearest_wolf en un pointeur de type wolf
  //moving_object *wolf_ptr = dynamic_cast<moving_object*>(nearest_wolf);
  

  if (distance(nearest_wolf) < AURA_KILL) {
    set_alive(false);
    return;
  }

  if(distance(nearest_wolf) < AURA_MOUTON) {
    set_speed(4*SPEED_MOUTON);
    set_direction_x(nearest_wolf->get_direction_x());
    set_direction_y(nearest_wolf->get_direction_y());
  }
  else{
    set_speed(SPEED_MOUTON);
  }

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
    set_speed(SPEED_WOLF);
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
wolf::~wolf() {
  SDL_FreeSurface(get_image_ptr());
}
void wolf::move(std::vector<std::shared_ptr<object>> characters) {

  object * neareast = get_nearest_object(SHEEP, characters);
  shepherd_dog * nearest_dog = dynamic_cast<shepherd_dog*>(get_nearest_object(SHEPHERD_DOG, characters));
  
  //transforme nearest_wolf en un pointeur de type wolf
  //moving_object *wolf_ptr = dynamic_cast<moving_object*>(neareast);
  if(distance(nearest_dog) < AURA_DOG){
    set_direction_x(get_x() - nearest_dog->get_x());
    set_direction_y(get_y() - nearest_dog->get_y() );
    set_speed(SPEED_WOLF*4);
  }
  else {
    set_direction_x(neareast->get_x() - get_x());
    set_direction_y(neareast->get_y() - get_y());
    set_speed(SPEED_WOLF);
  }
  float temp_taux = 0.1;
  temp_taux = sqrt(pow(get_direction_x(), 2) + pow(get_direction_y(), 2));
  set_x(get_x() + get_direction_x() * get_speed() / temp_taux);
  set_y(get_y() + get_direction_y() * get_speed() / temp_taux);


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



   // Load shepherd
 object_ptr_->add_character(std::make_shared<shepherd>("images/shepherd.png", window_surface_ptr_));


  // Load sheep
  
  



  // Load wolf
  
  for (unsigned i = 0; i < n_wolf; ++i) {
    object_ptr_->add_character(std::make_shared<wolf>("images/wolf.png", window_surface_ptr_));
  }
  for (unsigned i = 0; i < n_sheep; ++i) {
    object_ptr_->add_character(std::make_shared<sheep>("images/sheep.png", window_surface_ptr_));
  }
  for(unsigned i = 0; i < NB_SHEPHERD_DOG; ++i)
  {
    object_ptr_->add_character(std::make_shared<shepherd_dog>("images/dog.png", window_surface_ptr_,i));
  }

}

application::~application() {
  SDL_FreeSurface(window_surface_ptr_);
  SDL_DestroyWindow(window_ptr_);
  SDL_Quit();
}
void object::update() {
  // Move all animals
  for (auto it = characters.begin(); it != characters.end(); ) {
    (*it)->move(characters);
    (*it)->draw(window_surface_ptr_, (*it)->get_image_ptr());
    if (!(*it)->is_alive()) {
      it = characters.erase(it);
    } else {
      ++it;
    }
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

  object * shepherd_dog_selection = nullptr;
  //create shepherd and get the pointer of type SHEPHERD in object_ptr_ copy it to shepherd
  //shepherd * shphrd = dynamic_cast<shepherd *>(object_ptr_->get_characters_by_type(SHEPHERD));

  while (!quit) {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_QUIT) {
        quit = true;
      }
      //shphrd->handle_event(e);
      if(e.type == SDL_MOUSEBUTTONDOWN)
      {
        if(e.button.button == SDL_BUTTON_LEFT)
        {
          std :: cout << "x = " << e.button.x << " y = " << e.button.y << std :: endl;
          shepherd_dog_selection = get_shepherd_dog_selection(object_ptr_->get_characters(), e.button.x, e.button.y);
          if(shepherd_dog_selection != nullptr)
          {
            std :: cout << "shepherd dog selected" << std :: endl;
          }
        }
        if(e.button.button == SDL_BUTTON_RIGHT)
        {
          if(shepherd_dog_selection != nullptr)
          {
            shepherd_dog_selection->set_x_hunt(e.button.x);
            shepherd_dog_selection->set_y_hunt(e.button.y);
            shepherd_dog_selection->set_is_hunting(true);
            shepherd_dog_selection->set_go_hunt(true);
            shepherd_dog_selection = nullptr;
          }
        }
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

object * get_shepherd_dog_selection(std::vector<std::shared_ptr<object>> characters, int x_pos_mouse ,int y_pos_mouse)
{
    for(auto character = characters.begin(); character != characters.end(); ++character)
    {
      if((*character)->get_type() == SHEPHERD_DOG)
      {
        if((*character)->get_x() < x_pos_mouse && (*character)->get_x() + (*character)->get_shape_size() > x_pos_mouse)
        {
            if ((*character)->get_y() < y_pos_mouse && (*character)->get_y() + (*character)->get_shape_size() > y_pos_mouse)
            {
                return (*character).get();
            }
        }
      }
    }
    return NULL;
}





