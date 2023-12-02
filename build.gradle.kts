plugins {
    cpp
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
    testImplementation("org.junit.jupiter:junit-jupiter-api:5.8.1")
    testRuntimeOnly("org.junit.jupiter:junit-jupiter-engine:5.8.1")
}

tasks.test {
    systemProperty("java.library.path", "build/natives/lib")
    testLogging.showStandardStreams = true
    useJUnitPlatform()
}

sourceSets {
    main {
        resources {
            srcDirs("src/main/resources", "build/natives/lib")
        }
    }
}

tasks.withType<JavaCompile> {
    options.encoding = "UTF-8"
    options.compilerArgs.add("-h")
    options.compilerArgs.add(file("src/main/include").absolutePath)
}

val compileJNI = tasks.register<Task>("compileJNI") {
    dependsOn(tasks.compileJava)

    doLast {
        exec {
            commandLine("sh", "-c", "mkdir -p build/natives && cd build/natives && cmake ../.. && make")
        }
    }
}

tasks.processResources {
    dependsOn(compileJNI)
}

tasks.clean {
    doFirst {
        delete(fileTree("src/main/include") {
            include("jni_*.h")
        })
    }
}

application {
    mainClass.set("me.duncte123.lottieconverter.Main")
    applicationDefaultJvmArgs = listOf("-Djava.library.path=" + file("build/natives/lib").absolutePath)
}
