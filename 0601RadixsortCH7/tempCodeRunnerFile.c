    int cur = first;
    while(cur) {
        printf("%s %d %d\n", e[cur].name, e[cur].class, e[cur].num);
        cur = link[cur];
    }