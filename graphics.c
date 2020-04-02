#include <stdlib.h>
volatile int pixel_buffer_start; // global variable

void draw_line(int x0, int x1, int y0, int y1, short int line_color);
void draw_yline(int x,  short int line_color);
void draw_xline(int  y,  short int line_color);
void draw_board();
void clear_screen();
void plot_pixel(int x, int y, short int line_color);
void swap(int x0, int x1);
void wait_for_vsync();
int fill_rand(int* ptr, int a, int b); // fill ptr with a random number in [a, b]

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    
    //int xpoints[8];
    
    
    
    // declare other variables(not shown)
    // initialize location and direction of rectangles(not shown)

    /* set front pixel buffer to start of FPGA On-chip memory */
    /* now, swap the front/back buffers, to set the front buffer location */
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
    // pixel_buffer_start points to the pixel buffer
    /* set back pixel buffer to start of SDRAM memory */
    *(pixel_ctrl_ptr + 1) = 0xC0000000;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
    clear_screen();
    while (1)
    {
        /* Erase any boxes and lines that were drawn in the last iteration */
        
        
        
        

            

        // code for drawing the boxes and lines (not shown)
        // code for updating the locations of boxes (not shown)
        
    
       //Insert game logic
        
        draw_board();
        

        wait_for_vsync(); // swap front and back buffers on VGA vertical sync
        
        //Erase
        
        pixel_buffer_start = *(pixel_ctrl_ptr + 1); // new back buffer
        
        
        
        
        
    }
}

// code for subroutines (not shown)



void wait_for_vsync(){
    
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    *pixel_ctrl_ptr = 1;
    register int temp = *(pixel_ctrl_ptr+3);
    while((temp & 0x01) != 0) {
        temp = *(pixel_ctrl_ptr+3);
    }
    
}

// code not shown for clear_screen() and draw_line() subroutines

void draw_board(){
    for(int a = 0; a< 8 ; a++){
        
        //box1
        draw_yline(40 + a*30, 0x0000);
        draw_yline(69 + a*30, 0x0000);
        
    }
    for(int a = 0; a< 8 ; a++){
        
        //box1
        draw_xline(0  + a*30, 0x0000);
        draw_xline(29 + a*30, 0x0000);
        
    }
}

void draw_line(int x0, int y0, int x1, int y1, short int line_color){
    int is_steep = abs(y1 - y0) > abs(x1 - x0);
    if(is_steep){
        int temp = x0;
        x0 = y0;
        y0 = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
    }
    if(x0 > x1){
        int temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
    }
    int deltax = x1 - x0;
    int deltay = abs(y1 - y0);
    int error = -(deltax /2);
    int y = y0;
    int y_step;
    if(y0 < y1){
        y_step = 1;
    }else{
        y_step = -1;
    }
    for(int x = x0 ; x < x1 ; x++){
        if(is_steep){
            plot_pixel(y,x,line_color);
        }else{
            plot_pixel(x,y,line_color);
        }
        error = error + deltay;
        if(error >= 0){
            y = y + y_step;
            error = error - deltax;
        }
    }
        
}

void draw_xline( int y, short int line_color){
    
    for(int x = 40 ; x < 280 ; x++){
        plot_pixel(x,y,line_color);
    }
        
}
void draw_yline( int x, short int line_color){
    
    for(int y = 0 ; y < 240 ; y++){
        plot_pixel(x,y,line_color);
    }
        
}

void clear_screen(){
    for(int x = 0 ; x < 320 ; x++){
        for(int y = 0 ; y < 240 ; y++){
            plot_pixel(x,y,0xFFFF);
        }
    }
}



void plot_pixel(int x, int y, short int line_color)
{
    *(short int *)(pixel_buffer_start + (y << 10) + (x << 1)) = line_color;
}

int fill_rand(int* ptr, int a, int b) {
	*ptr = a + rand() % (b - a + 1);
}
