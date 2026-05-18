    for(int i = 0; i < q; i++){
        quick_sort(arr, i*S, i*S + S - 1);
    }
    if(size % S != 0){
        quick_sort(arr, q*S, size - 1);
    }