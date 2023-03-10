pipeline {
    agent any
    stages {
        stage('getting dependencies') {
            steps {
                sh 'chmod +x buildscripts/dep_builder.sh'
                sh './buildscripts/dep_builder.sh'
            }
        }
        
        stage('Build') {
            steps {
                def workspace = WORKSPACE
                sh 'cd ${workspace}'
                sh 'echo "building..."'
                sh 'cmake -B build -S .'
                sh 'cmake --build build'
            }
        }
        
        
        
    }
}
