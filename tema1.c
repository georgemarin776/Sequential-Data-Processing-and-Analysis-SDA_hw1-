#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef unsigned long long ull;
typedef unsigned short int usi;

typedef struct dlist{

    double value;
    ull timestamp;
    usi exists;
    struct dlist *next, *previous;
} dlist;

double max(double a, double b) {
    if(a > b)
        return a;
    return b;
}

double min(double a, double b) {
    return a + b - max(a, b);
}

double squared(double value) {
    
    return value * value;
}

void init(dlist **first, dlist **last) {

    *first = (dlist *)malloc(sizeof(dlist));
    *last = (dlist *)malloc(sizeof(dlist));

    (*first)->next = *last;
    (*first)->previous = *last;
    (*first)->exists = 0;

    (*last)->next = *first;
    (*last)->previous = *first;
    (*last)->exists = 0;

}

void clear(dlist **first, dlist **last) {

    dlist *Node = (*first)->next;

    while (Node != (*last)) {

        dlist *nextNode = Node->next;
        free(Node);
        Node = nextNode;
    }

    free(*first);
    free(*last);
}

void add(dlist *last, ull timestamp, double value) {

    dlist *newNode = NULL;

    newNode = (dlist *)malloc(sizeof(dlist));
    newNode->timestamp = timestamp;
    newNode->value = value;
    newNode->exists = 1;
    
    last->previous->next = newNode;
    newNode->previous = last->previous;
    newNode->next = last;
    last->previous = newNode;
}

int count_exists(dlist *first) {

    dlist *Node = first->next;
    int i = 0;

    while (Node != first->previous) {
        i += Node->exists;
        Node = Node->next;
    }

    return i;
}

void print(dlist *first) {

    dlist *Node = first->next;
    printf("%d\n", count_exists(first));

    while(Node != first->previous) {

        if(Node->exists)
            printf("%llu %.2lf\n", Node->timestamp, Node->value);

        Node = Node->next;
    }

}

void read(dlist *last, int *n) {

    int i;

    scanf("%d", n);

    for (i = 0; i < *n; i++) {
        ull timestamp;
        double value;

        scanf("%llu %lf", &timestamp, &value);
        add(last, timestamp, value);
    }
}

double medie(dlist *Node, int k) {

    int i;
    double sum = 0;

    for(i = 0; i < k; i++, Node = Node->next) {
        sum+= Node->value;        
    }

    return sum / k;
}

double deviatie(dlist *Node, int k) {
    
    int i;
    double sum = 0, x_m = medie(Node, k);

    for (i = 0; i < k; i++, Node = Node->next) {

        sum += squared(Node->value - x_m);
    }

    return sqrt(sum / k);
}

void rm(dlist *Node) {

    Node->next->previous = Node->previous;
    Node->previous->next = Node->next;
    free(Node);
}

void remove_nodes(dlist *first) {

    dlist *Node = first->next;

    while (Node != first->previous) {
        Node = Node->next;
        if (Node->previous->exists == 0)
            rm(Node->previous);
    }
}

void e1(dlist *first) {
    
    dlist *startNode = first->next, *finalNode = first->previous->previous;
    int i, k = 5;

    for (i = 0; i < k / 2; i++, startNode = startNode->next);
    for (i = 0; i < k / 2; i++, finalNode = finalNode->previous);

    //printf("%.2f %.2f\n", startNode->value, finalNode->value);

    for (dlist *Node = startNode; Node != finalNode->next; Node = Node->next) {
        
        dlist *medieNode = Node;
        for (i = 0; i < k/2; i++, medieNode = medieNode->previous);
        double value = Node->value, med = medie(medieNode, k), dev = deviatie(medieNode, k);

        //printf("average = %lf deviation = %lf %d\n", med, dev, value <= med + dev && value >= med - dev);

        if (value > med + dev || value < med - dev) {
            Node->exists = 0;
        }
    }

    remove_nodes(first);
}

double med3(double a, double b, double c) {

    return max(min(a, b), min(c, max(a, b)));
}

double med5(double a, double b, double c, double d, double e) {

    double f = max(min(a,b),min(c,d)); // discards lowest from first 4
    double g = min(max(a,b),max(c,d)); // discards biggest from first 4
    return med3(e, f, g);
}

double det_mid5(dlist *Node) {

    int i;

    float a = Node->value;
    Node = Node->next;

    float b = Node->value;
    Node = Node->next;

    float c = Node->value;
    Node = Node->next;

    float d = Node->value;
    Node = Node->next;

    float e = Node->value;

    return med5(a, b, c, d, e);
}

void e2(dlist *first) {

    dlist *startNode = first->next, *finalNode = first->previous->previous;
    dlist *first_e2 = NULL, *last_e2 = NULL;

    init(&first_e2, &last_e2);

    int i;

    for (i = 0; i < 2; i++, startNode = startNode->next);
    for (i = 0; i < 2; i++, finalNode = finalNode->previous);

    for (dlist *Node = startNode; Node != finalNode->next; Node = Node->next) {
        
        add(last_e2, Node->timestamp, det_mid5(Node->previous->previous));
    }

    //clear(&first, &(first->previous));
    *first = *first_e2;
    *(first->previous) = *last_e2;

}

void e3(dlist *first) {

    dlist *startNode = first->next, *finalNode = first->previous->previous;
    dlist *first_e2 = NULL, *last_e2 = NULL;

    init(&first_e2, &last_e2);

    int i;

    for (i = 0; i < 2; i++, startNode = startNode->next);
    for (i = 0; i < 2; i++, finalNode = finalNode->previous);

    for (dlist *Node = startNode; Node != finalNode->next; Node = Node->next) {
        
        add(last_e2, Node->timestamp, medie(Node->previous->previous, 5));
    }

    //clear(&first, &(first->previous));
    *first = *first_e2;
    *(first->previous) = *last_e2;
}

void u(dlist *first) {

    dlist *Node;
    int length = count_exists(first), i, sw = 1;

    for (i = 1, Node = first->next->next; i < length; i++, Node = Node->next) {

        ull timestamp = Node->timestamp - Node->previous->timestamp;
        if(timestamp >= 100 && timestamp <= 1000) {

            Node->timestamp = (Node->timestamp + Node->previous->timestamp) / 2;
            Node->value = (Node->value + Node->previous->value) / 2;
        }
    }
    
}

double w(double i, double k) {

    double sum = 0;
    int j;
    for (j = 0; j < 3; j++) {
        sum += squared(j / (k - 1)) * 0.9 + 0.1;
    }

    return (squared(i / (k - 1)) * 0.9 + 0.1) / sum;
}

void add_before(dlist *Node, ull timestamp, double value) {

    dlist *newNode = NULL;

    newNode = (dlist *)malloc(sizeof(dlist));

    newNode->timestamp = timestamp;
    newNode->value = value;
    newNode->exists = 1;

    newNode->previous = Node->previous;
    newNode->next = Node;

    Node->previous->next = newNode;
    Node->previous = newNode;
}

void c(dlist *first) {

    dlist *startNode = first->next, *finalNode = first->previous->previous;
    int i;

    /*
    dlist *first_e2 = NULL, *last_e2 = NULL;
    init(&first_e2, &last_e2);
    add(last_e2, startNode->timestamp, startNode->value);
    add(last_e2, startNode->next->timestamp, startNode->next->value);
    add(last_e2, startNode->next->next->timestamp, startNode->next->next->value);
    */

    for (i = 0; i < 2; i++, startNode = startNode->next);
    for (i = 0; i < 2; i++, finalNode = finalNode->previous);
   
    for (dlist *Node = startNode->next; Node != finalNode->next; Node = Node->next) {
        
        if (Node->timestamp - Node->previous->timestamp >= 1000) {

            int i;
            double w0 = w(0, 3), w1 = w(1, 3), w2 = w(2, 3);
            double prev_timestamp = Node->previous->timestamp, timestamp = Node->timestamp;
            double left_w2 = Node->previous->value, left_w1 = Node->previous->previous->value, left_w0 = Node->previous->previous->previous->value;
            double right_w2 = Node->value, right_w1 = Node->next->value, right_w0 = Node->next->next->value;
            //printf("%lf %lf %lf\n",  w0, w1, w2);

            for(i = prev_timestamp + 200; i < Node->timestamp; i += 200) {
                
                double C = (double)(i - prev_timestamp) / (timestamp - prev_timestamp);
                //printf("%d %lf\n", i, C);
                double left_sum = left_w2 * w2 + left_w1 * w1 + left_w0 * w0;
                double right_sum = right_w2 * w2 + right_w1 * w1 + right_w0 * w0;
                //add(last_e2, i, (1 - C) * left_sum + C * right_sum);
                add_before(Node, i, (1 - C) * left_sum + C * right_sum);
            }
        }
        //add(last_e2, Node->timestamp, Node->value);

    }

    /*
    add(last_e2, finalNode->next->timestamp, finalNode->next->value);
    add(last_e2, finalNode->next->next->timestamp, finalNode->next->next->value);

    //clear(&first, &(first->previous));

    /*
    first = *first_e2;
    (first->previous) = *last_e2;
    */
}

double max_t6(dlist *first) {

    dlist* Node = first->next;
    double mx = -INT_MAX;

    while(Node != first->previous) {

        mx = max(mx, Node->value);
        Node = Node->next;
    }

    return mx;
}

double min_t6(dlist *first) {

    dlist* Node = first->next;
    double mn = INT_MAX;

    while(Node != first->previous) {

        mn = min(mn, Node->value);
        Node = Node->next;
    }

    return mn;
}

void st(int delta, dlist *first) {

    double mx = max_t6(first), mn = min_t6(first);
    int i = mn / delta - 1, i_max = mx / delta + 2;

    for (; i < i_max; i++) {

        int count = 0;
        dlist *Node = first->next;

        while(Node != first->previous) {

            if (Node->value >= delta * i && Node->value <= delta * (i + 1))
                count++;
            Node = Node->next;
        }

        if (count) {
            printf("[%d, %d] %d\n", i * delta, (i + 1) * delta, count);
        }
    }
}

void call_fct(int argc, char *argv[], dlist *first, int *t6) {

    int i;
    for (i = 1; i < argc; i++) {

        if (strcmp(argv[i], "--e1") == 0)
            e1(first);
        else
            if (strcmp(argv[i], "--e2") == 0)
                e2(first);
        else
            if (strcmp(argv[i], "--e3") == 0)
                e3(first);
        else
            if (strcmp(argv[i], "--u") == 0)
                u(first);
        else
            if (strcmp(argv[i], "--c") == 0)
                c(first);
        else {
            st(atoi(argv[i] + 4), first);
            (*t6) = 1;
        }
    }
}

void main(int argc, char *argv[]) {

    dlist *first = NULL, *last = NULL;
    int n, t6 = 0;

    init(&first, &last);
    read(last, &n);

    call_fct(argc, argv, first, &t6);

    if(t6 == 0)
        print(first);
}