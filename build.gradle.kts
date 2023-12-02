plugins {
    java
    `java-library`
    application
}

group = "me.duncte123"
version = "1.0-SNAPSHOT"

repositories {
    mavenCentral()
}

java {
    sourceCompatibility = JavaVersion.VERSION_21
    targetCompatibility = JavaVersion.VERSION_21
}

dependencies {
    //
}

tasks.test {
    useJUnitPlatform()
}

application {
    mainClass.set("me.duncte123.lottieconverter.Main")
}
