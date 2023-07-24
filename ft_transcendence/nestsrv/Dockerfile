# Use the latest Alpine image as the base
FROM alpine:latest

# Set labels
LABEL maintainer="agiraude"
LABEL email="agiraude@student.42.fr"

# Install system dependencies
RUN apk update && \
  apk upgrade && \
  apk add --no-cache nodejs npm

# Create and set the working directory
WORKDIR /app

# Copy the NestJS application to the working directory
COPY trsc-server/ .

# Install application dependencies
RUN npm install

# Expose port 3000 for the NestJS application
EXPOSE 3000

# Set the entrypoint command to start the NestJS application
ENTRYPOINT [ "npm", "run", "start" ]
