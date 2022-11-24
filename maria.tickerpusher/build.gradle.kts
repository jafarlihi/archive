import org.jetbrains.kotlin.gradle.tasks.KotlinCompile
import org.gradle.jvm.tasks.Jar

plugins {
    java
    kotlin("jvm") version "1.3.41"
}

group = "hjaf.maria"
version = "0.0.1"

repositories {
    mavenCentral()
}

dependencies {
    implementation(kotlin("stdlib-jdk8"))
    testCompile("junit", "junit", "4.12")
    api("com.google.dagger", "dagger", "2.24")
    annotationProcessor("com.google.dagger", "dagger-compiler", "2.24")
    compile("org.apache.logging.log4j", "log4j-core", "2.12.1")
    compile("org.slf4j", "slf4j-log4j12", "1.7.28")
    compile("org.mongodb", "mongo-java-driver", "3.11.0")
    compile("io.prometheus", "simpleclient", "0.6.0")
    compile("io.prometheus", "simpleclient_pushgateway", "0.6.0")
    compile("org.knowm.xchange", "xchange-core", "4.3.21")
    compile("org.knowm.xchange", "xchange-kraken", "4.3.21")
}

val fatJar = task("fatJar", type = Jar::class) {
    baseName = "${project.name}-fat"
    manifest {
        attributes["Implementation-Version"] = version
        attributes["Main-Class"] = "hjaf.maria.tickerpusher.App"
    }
    from(configurations.runtimeClasspath.get().map({ if (it.isDirectory) it else zipTree(it) }))
    with(tasks.jar.get() as CopySpec)
}

tasks {
    "build" {
        dependsOn(fatJar)
    }
}

configure<JavaPluginConvention> {
    sourceCompatibility = JavaVersion.VERSION_11
}
tasks.withType<KotlinCompile> {
    kotlinOptions.jvmTarget = "11"
}