FROM debian:wheezy

RUN apt-get update
RUN apt-get install apt-utils -y;
RUN apt-get install clang -y ;
RUN apt-get install make -y;
RUN apt-get install binutils -y
RUN apt-get install git -y

# Tools
RUN apt-get install inetutils-traceroute -y
RUN apt-get install vim -y
RUN apt-get install tcpdump -y
RUN apt-get install nmap -y;


EXPOSE 22

CMD /bin/bash
