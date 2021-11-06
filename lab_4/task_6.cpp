#include <cstdio>
int main(){
    FILE *entrance, *output;
    entrance = fopen("garland.in", "r");
    output = fopen("garland.out", "w");
    int n;
    double h1; // заданная высота
    double left = 0; // меньшее из значений, когда вторая лампочка лежит на земле
    fscanf(entrance, "%d %lf", &n, &h1);
    double right = h1; // правая граница, равная высоте (это гарантирует, что след лампочки будут находиться выше)
    double last = -1;
    fclose(entrance);
    //выясняем правда ли, что мы можем отличить положение второй лампочки так, чтобы положение конечной лампочки было достаточно близким
    while(true){
        double m = (left + right) / 2;
        if(m == left || m == right){ //если среднее значение == левому или правому, то завершаем
            break;
        }
        double early = h1; // предыдущее значение
        double now = m; // текущее значение
        bool not_on_the_ground = now > 0; // выше земли тогда, когда текущее значение больше нуля

        for(int i = 3; i <= n; i++){ // номер лампочки, начиная с трёх
            double next = 2 * now - early + 2; // получаем высоту лампочки
            not_on_the_ground &= next > 0; // требуется, чтобы выше земли было, все, кто раньше был выше и при этом, чтобы некст > 0
            early = now;
            now = next;
        }

        if(not_on_the_ground){ // если оказалось выше земли, тогда мы понижаем правую границу
            right = m;
            last = now;
        }

        else{
            left = m;
        }
    }

    fprintf(output, "%.2f", last);
    fclose(output);
    return 0;
}
