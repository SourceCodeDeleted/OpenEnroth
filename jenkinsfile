pipeline {
    agent any
    stages {
        stage('getting dependencies') {
            steps {
                sh 'chmod +x dep_builder.sh'
                sh './dep_builder.sh'
            }
        }
        
        stage('Build') {
            steps {
                sh 'echo "building..."'
                sh 'cmake -B build -S .'
                sh 'cmake --build build'
            }
        }
        
        
        
    }
}
