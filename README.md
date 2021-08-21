It's 2021. I've been doing software development since I was 5, started again at 17 and never looked back since. And after all this damn time....I finally did C++. I wanted to know the bleeding edge best, and to level my game up outside of easy abstracted languages like Python & JavaScript. I realize the possibilities of C++ are near endless, and the fact that it's a level above assembly/metal is highly alluring. Serious tools & software like Amazon AWS Hyperplane are in C++ and in order to make the tools in the data center or routing protocols, what better way than to struggle in C++. 

This is 300 lines of C++ to make moving rainbow C++ much more faster than anything in Python & JavaScript. Worth the struggle.

Interesting ideas is to have the mouse influence the waves, or to make other moving plots/shapes

# rainbow_waves.cpp (excerpt)
------------
```cpp
for (int i = 0; i < line_count; i++)
        {
            //WAS A HUGE BUG (SIZE WAS TOO MUCH)
            vector<vector<float>> coordinates_line;
            for (float x = 0; x < rect.right; x = x + 5)
            {
                // cos(x/30) is the horizontal difference between waves
                // (rect.bottom/2-50) is 
                // cos(seperate_line_iteration) IS THE AMPLITUDE
                y = rect.bottom / 2 + cos(x / horizontal_wave_distance) * (rect.bottom / 2 - 50) * cos(separate_line_iteration);
                //NO LINE SPANNING THE HORIZONTAL SCREN
                coordinates_line.push_back({x,y});
            }

            separate_line_iteration = separate_line_iteration - distance_between_lines;
            coordinates_lines.push_back(coordinates_line);
            if(coordinates_lines.size() > line_count)
            {
                auto line_to_destroy = coordinates_lines.front();
                coordinates_lines.pop_front();
                line_to_destroy.clear();
            }
        }
```
