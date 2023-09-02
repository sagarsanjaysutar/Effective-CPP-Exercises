/**
 * @brief Item 26: Postpone variable definition as long as possible.
 * 
 * Define the variable right before its gonna be used, as opposed to define all of them at the start for formatting purposes.
 *
 * Risk Points:
 * 1. If an exception occurs b/w variable definition & it's usage, then the variable goes unused
 *  {
 *      int a;
 *      if(...){ throw exception;}
 *      ...
 *      a is used later
 *  }
 * 
 * 2. Constructor of variable should be called right before it's usage. 
 * If done before the usage, unnecessary default constructors are called. 
 * 
 */