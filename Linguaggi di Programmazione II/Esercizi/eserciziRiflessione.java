public void resetV1(Object x) throws IllegalAccessException { //azzera anche i campi ereditati
    Field[] allFields = x.getClass().getFields();
    for (Field f : allFields) {
        if (f.getType().equals(int.class)) {
            f.set(x, 0);
        }
    }
}

public void resetV2(Object x) throws IllegalAccessException { //azzera solo i campi propri
    Field[] allFields = x.getClass().getDeclaredFields();
    for (Field f : allFields) {
        if (f.getType().equals(int.class) && Modifier.isPublic(f.getModifiers())) {
            f.set(x, 0);
        }
    }
}

public Class<?> generalSuperclass(Object x) {
    Class<?> class1 = x.getClass();
    while (! (class1.getSuperclass().equals(Object.class)) ) {
        class1 = class1.getSuperclass();
    }
    return class1;
}