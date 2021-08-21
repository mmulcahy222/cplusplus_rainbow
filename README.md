It's 2021. I've been doing software development since I was 5, started again at 17 and never looked back since. And after all this damn time....I finally did C++. I wanted to know the bleeding edge best, and to level my game up outside of easy abstracted languages like Python & JavaScript. I realize the possibilities of C++ are near endless, and the fact that it's a level above assembly/metal is highly alluring. Serious tools & software like Amazon AWS Hyperplane are in C++ and in order to make the tools in the data center or routing protocols, what better way than to struggle in C++. 

This is 300 lines of C++ to make moving rainbow C++ much more faster than anything in Python & JavaScript. Worth the struggle.

Interesting ideas is to have the mouse influence the waves, or to make other moving plots/shapes

# rainbow_waves.cpp (excerpt)

```cpp
for (auto coordinates_line : coordinates_lines)
    {    
        for (auto coordinates : coordinates_line)
        {
            int x = (int)floor(coordinates[0]);
            int y = (int)floor(coordinates[1]);
            //remove the horizontal line, only show cosine waves
            if (x <= 0)
            {
                MoveToEx(hdcBuffer, x, y, 0);
                SelectObject(hdcBuffer, GetStockObject(DC_PEN));
                continue;
            }
            LineTo(hdcBuffer, x, (int)floor(y));
        }
        line_color_index = color_index + line_index;
        line_color_index = (line_color_index < 255) ? line_color_index : 0;
        SetDCPenColor(hdcBuffer, rainbow_generator(line_color_index));
        line_index += color_line_jitter;
    }
```
