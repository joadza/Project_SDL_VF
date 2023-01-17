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
constexpr unsigned AURA_KILL = 50;
constexpr unsigned SPEED_WOLF = 3;
constexpr unsigned SPEED_MOUTON = 2;
constexpr unsigned SPEED_DOG = 10;
constexpr unsigned AURA_MOUTON = 250;
#define ORBIT_SPEED 0.030f //speed of the shepherd dog
constexpr unsigned ORBIT_RADIUS = 170.0f; //radius of the shepherd dog
constexpr unsigned AURA_PROCREATION = 10; //aura of the sheep to procreate 
constexpr unsigned NB_SHEPHERD_DOG = 25;
constexpr unsigned AURA_DOG = 250;
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
  bool alive;
  // Some attribute to store all the wolves and sheep
  // here

  bool is_hunting;
  bool is_go_hunt;
  int x_hunt;
  int y_hunt;

public:
  object(SDL_Surface* window_surface_ptr); // todo: Ctor
  ~object(){}; // todo: Dtor, again for clean up (if necessary)
  void add_character(std::shared_ptr<object> character_ptr);
  void draw(SDL_Surface *window_surface_ptr, SDL_Surface *image_surface_ptr);
  void update(); // todo: "refresh the screen": Move animals and draw them
  virtual void move(std::vector<std::shared_ptr<object>> characters);
  void set_x(int x);
  void set_y(int y);
  int get_x() const;
  int get_y() const;
  void set_shape_size(int shape_size);
  int get_shape_size() const;
  // get characters
  std::vector<std::shared_ptr<object>> get_characters() const;
  void set_image_ptr(SDL_Surface* image_ptr);
  SDL_Surface* get_image_ptr() const;
  Type get_type() const;
  void set_type(Type type);
  void set_alive(bool alive);
  object * get_nearest_object(Type type,std::vector<std::shared_ptr<object>> characters);
  int distance(object * object);
  bool is_alive();
  object * get_characters_by_type(Type type, std::vector<std::shared_ptr<object>> characters);

  void set_x_hunt(int x);
  void set_y_hunt(int y);
  int get_x_hunt() const;
  int get_y_hunt() const;
  void set_is_hunting(bool is_hunting_);
  bool get_is_hunting() const;
  void set_go_hunt(bool go_hunt_);
  bool get_go_hunt() const;


  float get_direction_x() const;
      float get_direction_y() const;
      void set_direction_x(float direction_x);
      void set_direction_y(float direction_y);
      float direction_x;
      float direction_y;

  // todo: Draw all animals
  
                 // Note that this function is not virtual, it does not depend
                 // on the static type of the instance
  // Possibly other methods, depends on your implementation
};

object * get_shepherd_dog_selection(std::vector<std::shared_ptr<object>> characters, int x_pos_mouse ,int y_pos_mouse);

class moving_object : public object
{
    // todo: Define the attributes of a moving object
    private:
      float speed;
      
      
    public:
      moving_object(SDL_Surface* window_surface_ptr);
      ~moving_object(){}; // todo: Dtor, again for clean up (if necessary)
      float get_speed() const;
      
      void set_speed(float speed);
      

     
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
  bool time;

public:
  animal(const std::string& file_path, SDL_Surface* window_surface_ptr);
  // todo: The constructor has to load the sdl_surface that corresponds to the
  // texture
  ~animal(){}; // todo: Use the destructor to release memory and "clean up
               // behind you"
 // todo: Move the animals
 
};


class shepherd_dog : public animal {
    public:
        shepherd_dog(const std::string& file_path, SDL_Surface* window_surface_ptr,int i);
        ~shepherd_dog();
        /*
        * @brief: Maj position of the sheep
        *
        * @param: wolves: a array of wolves
        * @param: other: other animal
        * @param: size: size of the wolves array
        * @param: size_other: size of the other array
        */
        void move(std::vector<std::shared_ptr<object>> characters);
        shepherd_dog * get_shepherd_dog_selection(std::vector<std::shared_ptr<object>> characters, int x_pos_mouse ,int y_pos_mouse);
        //set and get is hunting
        
        void set_angle(float angle);
        float get_angle() const;
        



    private:
        float angle;


};

class playable_character : public moving_object {

private:
  SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                    // animal to be drawn, also non-owning
  SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use
                           // load_surface_for
  public:
  playable_character(const std::string& file_path, SDL_Surface* window_surface_ptr);
  ~playable_character(); // todo: Use the destructor to release memory and "clean up
               // behind you"
  virtual void handle_event(SDL_Event& event) = 0;
};

class shepherd : public playable_character {
  private:
    SDL_Surface* window_surface_ptr_; // ptr to the surface on which we want the
                                      // animal to be drawn, also non-owning
    SDL_Surface* image_ptr_; // The texture of the sheep (the loaded image), use

  public:
  shepherd(const std::string& file_path, SDL_Surface* window_surface_ptr);
  ~shepherd(); // todo: Use the destructor to release memory and "clean up
               // behind you"
  void handle_event(SDL_Event& event);
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
  ~sheep(); // todo: Use the destructor to release memory and "clean up
               // behind you"
  void move(std::vector<std::shared_ptr<object>> characters);
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
  ~wolf(); // todo: Use the destructor to release memory and "clean up
               // behind you"
  void move(std::vector<std::shared_ptr<object>> characters);

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