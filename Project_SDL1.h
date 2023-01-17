// SDL_Test.h: Includedatei für Include-Standardsystemdateien
// oder projektspezifische Includedateien.

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <vector>

// Defintions
constexpr double frame_rate = 60.0; // refresh rate
constexpr double frame_time = 1. / frame_rate;
constexpr unsigned SCREEN_WIDTH = 1920; // Width of window in pixel
constexpr unsigned SCREEN_HEIGHT = 1080; // Height of window in pixel
constexpr unsigned TAILLE_MAX_X = 1613;
constexpr unsigned TAILLE_MIN_X = 230;
constexpr unsigned TAILLE_MAX_Y = 868;
constexpr unsigned TAILLE_MIN_Y = 180;
// Minimal distance of animals to the border
// of the screen

constexpr unsigned frame_boundary = 100;

enum Gender {FEMELLE,MALE};

enum Type {SHEEP,WOLF,BACKGROUND,SHEPHERD_DOG,SHEPHERD};
// Helper function to initialize SDL
void init();

class object{
private:
  // Attention, NON-OWNING ptr, again to the screen
  SDL_Surface* window_surface_ptr_;
  SDL_Surface* image_ptr_;
  int shape_size;
  std::vector<std::shared_ptr<object>> characters;
  int x;
  int y;
  Type type;
  // Some attribute to store all the wolves and sheep
  // here

public:
  object(SDL_Surface* window_surface_ptr); // todo: Ctor
  ~object(){}; // todo: Dtor, again for clean up (if necessary)
  void add_character(std::shared_ptr<object> character_ptr);
  void draw(SDL_Surface *window_surface_ptr, SDL_Surface *image_surface_ptr);
  void update(); // todo: "refresh the screen": Move animals and draw them
  virtual void move(); // todo: Move the animals
  void set_x(int x);
  void set_y(int y);
  int get_x() const;
  int get_y() const;
  void set_shape_size(int shape_size);
  // get characters
  std::vector<std::shared_ptr<object>> get_characters() const;
  void set_image_ptr(SDL_Surface* image_ptr);
  SDL_Surface* get_image_ptr() const;
  Type get_type() const;
  void set_type(Type type);
  object * get_nearest_object(Type type);

  // todo: Draw all animals
  
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance
  // Possibly other methods, depends on your implementation
};


class moving_object : public object
{
    // todo: Define the attributes of a moving object
    private:
      float speed;
      float direction_x;
      float direction_y;
      
    public:
      moving_object(SDL_Surface* window_surface_ptr);
      ~moving_object(){}; // todo: Dtor, again for clean up (if necessary)
      float get_speed() const;
      float get_direction_x() const;
      float get_direction_y() const;

      void set_speed(float speed);
      void set_direction_x(float direction_x);
      void set_direction_y(float direction_y);

     
};


// The "object" on which all the animals live (like the std::vector
// in the zoo example).





class non_moveable_object : public object {
    public:
      non_moveable_object(const std::string& file_path, SDL_Surface* window_surface_ptr);
      ~non_moveable_object(){}; // todo: Dtor, again for clean up (if necessary)
      
};

class background : public non_moveable_object {
    private:
      SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                        // background to be drawn, also non-owning
      SDL_Surface* image_ptr_; // The texture of the background (the loaded image),
                               // use load_surface_for
    public:
      background(const std::string& file_path, SDL_Surface* window_surface_ptr);
      ~background(); // todo: Dtor, again for clean up (if necessary)
      SDL_Surface* get_image_ptr() const;
};





class animal : public moving_object {
private:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for
  // todo: Attribute(s) to define its position
  bool alive;
  bool time;

public:
  animal(const std::string& file_path, SDL_Surface* window_surface_ptr);
  // todo: The constructor has to load the sdl_surface that corresponds to the
  // texture
  ~animal(){}; // todo: Use the destructor to release memory and "clean up
               // behind you"
  bool get_alive() const;
  void set_alive(bool alive);
 // todo: Move the animals
 
};

// Insert here:
// class sheep, derived from animal
class sheep : public animal {

private:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
  Gender sexe;
public:
  sheep(const std::string& file_path, SDL_Surface* window_surface_ptr);
  void move();
  // todo
  // Ctor
  // Dtor
  // implement functions that are purely virtual in base class
};


class wolf : public animal {

private:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
  
public:
  wolf(const std::string& file_path, SDL_Surface* window_surface_ptr);
  void move();

  // todo
  // Ctor
  // Dtor
  // implement functions that are purely virtual in base class
};


// Insert here:
// class wolf, derived from animal
// Use only sheep at first. Once the application works
// for sheep you can add the wolves


// The application class, which is in charge of generating the window
class application {
private:
  // The following are OWNING ptrs
  SDL_Window* window_ptr_;
  SDL_Surface* window_surface_ptr_;
  SDL_Event window_event_;
  object *object_ptr_;
  object *sheep_ptr_;

  // Other attributes here, for example an instance of object

public:
  application(unsigned n_sheep, unsigned n_wolf); // Ctor
  ~application();                                 // dtor

  int loop(unsigned period); // main loop of the application.
                             // this ensures that the screen is updated
                             // at the correct rate.
                             // See SDL_GetTicks() and SDL_Delay() to enforce a
                             // duration the application should terminate after
                             // 'period' seconds
};