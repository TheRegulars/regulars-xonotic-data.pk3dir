FROM bacher09/xonplaces:latest
RUN adduser -D -h /xonotic xonotic && \
    mkdir -p /xonotic/userdata && \
    chown -R xonotic:xonotic /xonotic

USER xonotic:xonotic
COPY data /xonotic/data
COPY xonotic/*.d0pk xonotic/COPYING xonotic/GPL-3 xonotic/GPL-2 /xonotic/
VOLUME /xonotic/userdata
WORKDIR /xonotic
CMD ["/usr/bin/darkplaces-dedicated", "-xonotic", "-userdir", "/xonotic/userdata"]
